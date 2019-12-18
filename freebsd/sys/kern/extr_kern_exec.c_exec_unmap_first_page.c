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
typedef  int /*<<< orphan*/  vm_page_t ;
struct image_params {int /*<<< orphan*/ * firstpage; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_ACTIVE ; 
 int /*<<< orphan*/  sf_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sf_buf_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unwire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
exec_unmap_first_page(struct image_params *imgp)
{
	vm_page_t m;

	if (imgp->firstpage != NULL) {
		m = sf_buf_page(imgp->firstpage);
		sf_buf_free(imgp->firstpage);
		imgp->firstpage = NULL;
		vm_page_unwire(m, PQ_ACTIVE);
	}
}