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
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 struct mtx* vm_page_lockptr (int /*<<< orphan*/ ) ; 

void
vm_page_change_lock(vm_page_t m, struct mtx **mtx)
{
	struct mtx *mtx1;

	mtx1 = vm_page_lockptr(m);
	if (*mtx == mtx1)
		return;
	if (*mtx != NULL)
		mtx_unlock(*mtx);
	*mtx = mtx1;
	mtx_lock(mtx1);
}