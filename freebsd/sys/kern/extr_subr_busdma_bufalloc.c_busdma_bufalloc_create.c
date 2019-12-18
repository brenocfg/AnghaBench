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
typedef  int /*<<< orphan*/ * uma_free ;
typedef  int /*<<< orphan*/ * uma_alloc ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct busdma_bufzone {int size; int /*<<< orphan*/ * umazone; int /*<<< orphan*/  name; } ;
struct busdma_bufalloc {int min_size; int /*<<< orphan*/  num_zones; struct busdma_bufzone* buf_zones; } ;
typedef  struct busdma_bufalloc* busdma_bufalloc_t ;
typedef  int bus_size_t ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int) ; 
 int MAX_ZONE_BUFSIZE ; 
 int /*<<< orphan*/  MIN_ZONE_BUFSIZE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  busdma_bufalloc_destroy (struct busdma_bufalloc*) ; 
 struct busdma_bufalloc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int nitems (struct busdma_bufzone*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uma_zcreate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_allocf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zone_set_freef (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

busdma_bufalloc_t 
busdma_bufalloc_create(const char *name, bus_size_t minimum_alignment,
    uma_alloc alloc_func, uma_free free_func, u_int32_t zcreate_flags)
{
	struct busdma_bufalloc *ba;
	struct busdma_bufzone *bz;
	int i;
	bus_size_t cursize;

	ba = malloc(sizeof(struct busdma_bufalloc), M_DEVBUF, 
	    M_ZERO | M_WAITOK);

	ba->min_size = MAX(MIN_ZONE_BUFSIZE, minimum_alignment);

	/*
	 * Each uma zone is created with an alignment of size-1, meaning that
	 * the alignment is equal to the size (I.E., 64 byte buffers are aligned
	 * to 64 byte boundaries, etc).  This allows for a fast efficient test
	 * when deciding whether a pool buffer meets the constraints of a given
	 * tag used for allocation: the buffer is usable if tag->alignment <=
	 * bufzone->size.
	 */
	for (i = 0, bz = ba->buf_zones, cursize = ba->min_size;
	    i < nitems(ba->buf_zones) && cursize <= MAX_ZONE_BUFSIZE;
	    ++i, ++bz, cursize <<= 1) {
		snprintf(bz->name, sizeof(bz->name), "dma %.10s %ju",
		    name, (uintmax_t)cursize);
		bz->size = cursize;
		bz->umazone = uma_zcreate(bz->name, bz->size,
		    NULL, NULL, NULL, NULL, bz->size - 1, zcreate_flags);
		if (bz->umazone == NULL) {
			busdma_bufalloc_destroy(ba);
			return (NULL);
		}
		if (alloc_func != NULL)
			uma_zone_set_allocf(bz->umazone, alloc_func);
		if (free_func != NULL)
			uma_zone_set_freef(bz->umazone, free_func);
		++ba->num_zones;
	}

	return (ba);
}