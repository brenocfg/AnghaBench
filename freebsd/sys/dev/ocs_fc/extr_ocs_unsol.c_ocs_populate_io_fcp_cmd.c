#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  seq_init; scalar_t__ cs_ctl; scalar_t__ transferred; int /*<<< orphan*/  exp_xfer_len; int /*<<< orphan*/  init_task_tag; } ;
typedef  TYPE_1__ ocs_io_t ;
struct TYPE_8__ {int /*<<< orphan*/  additional_fcp_cdb_length; int /*<<< orphan*/  fcp_cdb_and_dl; } ;
typedef  TYPE_2__ fcp_cmnd_iu_t ;
struct TYPE_9__ {scalar_t__ cs_ctl; int /*<<< orphan*/  f_ctl; int /*<<< orphan*/  ox_id; } ;
typedef  TYPE_3__ fc_header_t ;

/* Variables and functions */
 int FC_FCTL_PRIORITY_ENABLE ; 
 int fc_be24toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocs_populate_io_fcp_cmd(ocs_io_t *io, fcp_cmnd_iu_t *cmnd, fc_header_t *fchdr, uint8_t sit)
{
	uint32_t	*fcp_dl;
	io->init_task_tag = ocs_be16toh(fchdr->ox_id);
	/* note, tgt_task_tag, hw_tag  set when HW io is allocated */
	fcp_dl = (uint32_t*)(&(cmnd->fcp_cdb_and_dl));
	fcp_dl += cmnd->additional_fcp_cdb_length;
	io->exp_xfer_len = ocs_be32toh(*fcp_dl);
	io->transferred = 0;

	/* The upper 7 bits of CS_CTL is the frame priority thru the SAN.
	 * Our assertion here is, the priority given to a frame containing
	 * the FCP cmd should be the priority given to ALL frames contained
	 * in that IO. Thus we need to save the incoming CS_CTL here.
	 */
	if (fc_be24toh(fchdr->f_ctl) & FC_FCTL_PRIORITY_ENABLE) {
		io->cs_ctl = fchdr->cs_ctl;
	} else {
		io->cs_ctl = 0;
	}
	io->seq_init = sit;
}