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
typedef  scalar_t__ cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_bounce_mtx ; 
 scalar_t__ of_bounce_phys ; 
 int /*<<< orphan*/ * of_bounce_virt ; 

__attribute__((used)) static void
ofw_real_unmap(cell_t physaddr, void *buf, size_t len)
{
	mtx_assert(&of_bounce_mtx, MA_OWNED);

	if (of_bounce_virt == NULL)
		return;

	if (physaddr == 0)
		return;

	memcpy(buf,of_bounce_virt + (physaddr - of_bounce_phys),len);
}