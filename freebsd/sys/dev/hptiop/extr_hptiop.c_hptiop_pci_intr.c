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
struct hpt_iop_hba {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iop_intr ) (struct hpt_iop_hba*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hptiop_lock_adapter (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  hptiop_unlock_adapter (struct hpt_iop_hba*) ; 
 int /*<<< orphan*/  stub1 (struct hpt_iop_hba*) ; 

__attribute__((used)) static void hptiop_pci_intr(void *arg)
{
	struct hpt_iop_hba * hba = (struct hpt_iop_hba *)arg;
	hptiop_lock_adapter(hba);
	hba->ops->iop_intr(hba);
	hptiop_unlock_adapter(hba);
}