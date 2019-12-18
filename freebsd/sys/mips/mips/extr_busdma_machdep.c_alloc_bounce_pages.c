#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_offset_t ;
typedef  scalar_t__ u_int ;
struct bounce_zone {int /*<<< orphan*/  free_bpages; int /*<<< orphan*/  total_bpages; int /*<<< orphan*/  bounce_page_list; int /*<<< orphan*/  lowaddr; } ;
struct bounce_page {scalar_t__ vaddr; int /*<<< orphan*/  busaddr; void* vaddr_nocache; } ;
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_3__ {struct bounce_zone* bounce_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BOUNCE ; 
 int /*<<< orphan*/  M_BUSDMA ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bounce_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bounce_lock ; 
 scalar_t__ contigmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct bounce_page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 scalar_t__ pmap_mapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_bpages ; 

__attribute__((used)) static int
alloc_bounce_pages(bus_dma_tag_t dmat, u_int numpages)
{
	struct bounce_zone *bz;
	int count;

	bz = dmat->bounce_zone;
	count = 0;
	while (numpages > 0) {
		struct bounce_page *bpage;

		bpage = (struct bounce_page *)malloc(sizeof(*bpage), M_BUSDMA,
						     M_NOWAIT | M_ZERO);

		if (bpage == NULL)
			break;
		bpage->vaddr = (vm_offset_t)contigmalloc(PAGE_SIZE, M_BOUNCE,
							 M_NOWAIT, 0ul,
							 bz->lowaddr,
							 PAGE_SIZE,
							 0);
		if (bpage->vaddr == 0) {
			free(bpage, M_BUSDMA);
			break;
		}
		bpage->busaddr = pmap_kextract(bpage->vaddr);
		bpage->vaddr_nocache =
		    (vm_offset_t)pmap_mapdev(bpage->busaddr, PAGE_SIZE);
		mtx_lock(&bounce_lock);
		STAILQ_INSERT_TAIL(&bz->bounce_page_list, bpage, links);
		total_bpages++;
		bz->total_bpages++;
		bz->free_bpages++;
		mtx_unlock(&bounce_lock);
		count++;
		numpages--;
	}
	return (count);
}