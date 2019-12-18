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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ va; } ;
struct xbb_softc {int reqlist_kva_pages; int kva; int /*<<< orphan*/  lock; int /*<<< orphan*/  kva_shortages; int /*<<< orphan*/  flags; TYPE_1__ ring_config; int /*<<< orphan*/  kva_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 intptr_t PAGE_SIZE ; 
 int /*<<< orphan*/  XBBF_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  bit_ffc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  bit_nset (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint8_t *
xbb_get_kva(struct xbb_softc *xbb, int nr_pages)
{
	int first_clear;
	int num_clear;
	uint8_t *free_kva;
	int      i;

	KASSERT(nr_pages != 0, ("xbb_get_kva of zero length"));

	first_clear = 0;
	free_kva = NULL;

	mtx_lock(&xbb->lock);

	/*
	 * Look for the first available page.  If there are none, we're done.
	 */
	bit_ffc(xbb->kva_free, xbb->reqlist_kva_pages, &first_clear);

	if (first_clear == -1)
		goto bailout;

	/*
	 * Starting at the first available page, look for consecutive free
	 * pages that will satisfy the user's request.
	 */
	for (i = first_clear, num_clear = 0; i < xbb->reqlist_kva_pages; i++) {
		/*
		 * If this is true, the page is used, so we have to reset
		 * the number of clear pages and the first clear page
		 * (since it pointed to a region with an insufficient number
		 * of clear pages).
		 */
		if (bit_test(xbb->kva_free, i)) {
			num_clear = 0;
			first_clear = -1;
			continue;
		}

		if (first_clear == -1)
			first_clear = i;

		/*
		 * If this is true, we've found a large enough free region
		 * to satisfy the request.
		 */
		if (++num_clear == nr_pages) {

			bit_nset(xbb->kva_free, first_clear,
				 first_clear + nr_pages - 1);

			free_kva = xbb->kva +
				(uint8_t *)((intptr_t)first_clear * PAGE_SIZE);

			KASSERT(free_kva >= (uint8_t *)xbb->kva &&
				free_kva + (nr_pages * PAGE_SIZE) <=
				(uint8_t *)xbb->ring_config.va,
				("Free KVA %p len %d out of range, "
				 "kva = %#jx, ring VA = %#jx\n", free_kva,
				 nr_pages * PAGE_SIZE, (uintmax_t)xbb->kva,
				 (uintmax_t)xbb->ring_config.va));
			break;
		}
	}

bailout:

	if (free_kva == NULL) {
		xbb->flags |= XBBF_RESOURCE_SHORTAGE;
		xbb->kva_shortages++;
	}

	mtx_unlock(&xbb->lock);

	return (free_kva);
}