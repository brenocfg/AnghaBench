#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ses_elm_ata_hdr {int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct TYPE_5__ {struct ses_elm_ata_hdr* ata; } ;
struct ses_addl_status {TYPE_1__ proto_hdr; } ;
struct sbuf {int dummy; } ;
struct TYPE_6__ {struct ses_addl_status addl; } ;
typedef  TYPE_2__ ses_element_t ;
struct TYPE_7__ {TYPE_2__* elm_private; } ;
typedef  TYPE_3__ enc_element_t ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_4btoul (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ses_print_addl_data_ata(struct sbuf *sbp, enc_element_t *obj)
{
	ses_element_t *elmpriv = obj->elm_private;
	struct ses_addl_status *addl = &elmpriv->addl;
	struct ses_elm_ata_hdr *ata = addl->proto_hdr.ata;

	sbuf_printf(sbp, ", SATA Slot: scbus%d target %d\n",
	    scsi_4btoul(ata->bus), scsi_4btoul(ata->target));
}