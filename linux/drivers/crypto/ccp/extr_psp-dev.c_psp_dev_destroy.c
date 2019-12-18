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
struct sp_device {struct psp_device* psp_data; } ;
struct psp_device {scalar_t__ sev_misc; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* misc_dev ; 
 int /*<<< orphan*/  sev_exit ; 
 int /*<<< orphan*/  sp_free_psp_irq (struct sp_device*,struct psp_device*) ; 

void psp_dev_destroy(struct sp_device *sp)
{
	struct psp_device *psp = sp->psp_data;

	if (!psp)
		return;

	if (psp->sev_misc)
		kref_put(&misc_dev->refcount, sev_exit);

	sp_free_psp_irq(sp, psp);
}