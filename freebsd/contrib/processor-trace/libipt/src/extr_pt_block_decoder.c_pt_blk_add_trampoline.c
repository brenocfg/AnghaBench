#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct pt_block_cache {int dummy; } ;
struct pt_bcache_entry {int ninsn; int mode; int /*<<< orphan*/  qualifier; scalar_t__ displacement; } ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  enum pt_exec_mode { ____Placeholder_pt_exec_mode } pt_exec_mode ;
typedef  int /*<<< orphan*/  bce ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_bcache_entry*,int /*<<< orphan*/ ,int) ; 
 int pt_bcache_add (struct pt_block_cache*,scalar_t__,struct pt_bcache_entry) ; 
 int /*<<< orphan*/  ptbq_again ; 
 int /*<<< orphan*/  ptbq_decode ; 

__attribute__((used)) static inline int pt_blk_add_trampoline(struct pt_block_cache *bcache,
					uint64_t ip, uint64_t nip,
					enum pt_exec_mode mode)
{
	struct pt_bcache_entry bce;
	int64_t disp;

	/* The displacement from @ip to @nip for the trampoline. */
	disp = (int64_t) (nip - ip);

	memset(&bce, 0, sizeof(bce));
	bce.displacement = (int32_t) disp;
	bce.ninsn = 1;
	bce.mode = mode;
	bce.qualifier = ptbq_again;

	/* If we can't reach @nip without overflowing the displacement field, we
	 * have to stop and re-decode the instruction at @ip.
	 */
	if ((int64_t) bce.displacement != disp) {

		memset(&bce, 0, sizeof(bce));
		bce.ninsn = 1;
		bce.mode = mode;
		bce.qualifier = ptbq_decode;
	}

	return pt_bcache_add(bcache, ip, bce);
}