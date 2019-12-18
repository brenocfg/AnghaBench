#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct atm_vcc* atmvcc; int /*<<< orphan*/  buf; } ;
struct TYPE_7__ {struct atm_vcc* atmvcc; int /*<<< orphan*/  buf; } ;
struct lanai_vcc {scalar_t__ nref; TYPE_4__ tx; int /*<<< orphan*/ * vbase; TYPE_3__ rx; } ;
struct lanai_dev {scalar_t__ naal0; int /*<<< orphan*/  pci; struct atm_vcc* cbrvcc; } ;
struct TYPE_6__ {scalar_t__ aal; } ;
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/ * dev_data; TYPE_2__ qos; TYPE_1__* dev; } ;
struct TYPE_5__ {scalar_t__ dev_data; } ;

/* Variables and functions */
 scalar_t__ ATM_AAL0 ; 
 int /*<<< orphan*/  ATM_VF_ADDR ; 
 int /*<<< orphan*/  ATM_VF_PARTIAL ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  aal0_buffer_free (struct lanai_dev*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host_vcc_unbind (struct lanai_dev*,struct lanai_vcc*) ; 
 int /*<<< orphan*/  kfree (struct lanai_vcc*) ; 
 int /*<<< orphan*/  lanai_buf_deallocate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lanai_cbr_shutdown (struct lanai_dev*) ; 
 int /*<<< orphan*/  lanai_shutdown_rx_vci (struct lanai_vcc*) ; 
 int /*<<< orphan*/  lanai_shutdown_tx_vci (struct lanai_dev*,struct lanai_vcc*) ; 

__attribute__((used)) static void lanai_close(struct atm_vcc *atmvcc)
{
	struct lanai_vcc *lvcc = (struct lanai_vcc *) atmvcc->dev_data;
	struct lanai_dev *lanai = (struct lanai_dev *) atmvcc->dev->dev_data;
	if (lvcc == NULL)
		return;
	clear_bit(ATM_VF_READY, &atmvcc->flags);
	clear_bit(ATM_VF_PARTIAL, &atmvcc->flags);
	if (lvcc->rx.atmvcc == atmvcc) {
		lanai_shutdown_rx_vci(lvcc);
		if (atmvcc->qos.aal == ATM_AAL0) {
			if (--lanai->naal0 <= 0)
				aal0_buffer_free(lanai);
		} else
			lanai_buf_deallocate(&lvcc->rx.buf, lanai->pci);
		lvcc->rx.atmvcc = NULL;
	}
	if (lvcc->tx.atmvcc == atmvcc) {
		if (atmvcc == lanai->cbrvcc) {
			if (lvcc->vbase != NULL)
				lanai_cbr_shutdown(lanai);
			lanai->cbrvcc = NULL;
		}
		lanai_shutdown_tx_vci(lanai, lvcc);
		lanai_buf_deallocate(&lvcc->tx.buf, lanai->pci);
		lvcc->tx.atmvcc = NULL;
	}
	if (--lvcc->nref == 0) {
		host_vcc_unbind(lanai, lvcc);
		kfree(lvcc);
	}
	atmvcc->dev_data = NULL;
	clear_bit(ATM_VF_ADDR, &atmvcc->flags);
}