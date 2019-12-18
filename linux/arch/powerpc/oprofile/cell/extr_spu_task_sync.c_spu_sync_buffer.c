#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vma_to_fileoffset_map {int dummy; } ;
struct spu {int dummy; } ;
struct cached_info {struct spu* the_spu; struct vma_to_fileoffset_map* map; } ;
struct TYPE_2__ {int last_guard_val; scalar_t__ ctx_sw_seen; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_lock ; 
 int /*<<< orphan*/  cache_lock ; 
 struct cached_info* get_cached_info (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* spu_buff ; 
 int /*<<< orphan*/  spu_buff_add (unsigned long long,int) ; 
 unsigned long long vma_map_lookup (struct vma_to_fileoffset_map*,unsigned int,struct spu*,int*) ; 

void spu_sync_buffer(int spu_num, unsigned int *samples,
		     int num_samples)
{
	unsigned long long file_offset;
	unsigned long flags;
	int i;
	struct vma_to_fileoffset_map *map;
	struct spu *the_spu;
	unsigned long long spu_num_ll = spu_num;
	unsigned long long spu_num_shifted = spu_num_ll << 32;
	struct cached_info *c_info;

	/* We need to obtain the cache_lock here because it's
	 * possible that after getting the cached_info, the SPU job
	 * corresponding to this cached_info may end, thus resulting
	 * in the destruction of the cached_info.
	 */
	spin_lock_irqsave(&cache_lock, flags);
	c_info = get_cached_info(NULL, spu_num);
	if (!c_info) {
		/* This legitimately happens when the SPU task ends before all
		 * samples are recorded.
		 * No big deal -- so we just drop a few samples.
		 */
		pr_debug("SPU_PROF: No cached SPU contex "
			  "for SPU #%d. Dropping samples.\n", spu_num);
		goto out;
	}

	map = c_info->map;
	the_spu = c_info->the_spu;
	spin_lock(&buffer_lock);
	for (i = 0; i < num_samples; i++) {
		unsigned int sample = *(samples+i);
		int grd_val = 0;
		file_offset = 0;
		if (sample == 0)
			continue;
		file_offset = vma_map_lookup( map, sample, the_spu, &grd_val);

		/* If overlays are used by this SPU application, the guard
		 * value is non-zero, indicating which overlay section is in
		 * use.	 We need to discard samples taken during the time
		 * period which an overlay occurs (i.e., guard value changes).
		 */
		if (grd_val && grd_val != spu_buff[spu_num].last_guard_val) {
			spu_buff[spu_num].last_guard_val = grd_val;
			/* Drop the rest of the samples. */
			break;
		}

		/* We must ensure that the SPU context switch has been written
		 * out before samples for the SPU.  Otherwise, the SPU context
		 * information is not available and the postprocessing of the
		 * SPU PC will fail with no available anonymous map information.
		 */
		if (spu_buff[spu_num].ctx_sw_seen)
			spu_buff_add((file_offset | spu_num_shifted),
					 spu_num);
	}
	spin_unlock(&buffer_lock);
out:
	spin_unlock_irqrestore(&cache_lock, flags);
}