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
typedef  void* uint8_t ;
struct hwrm_fw_reset_output {void* selfrst_status; } ;
struct hwrm_fw_reset_input {void* selfrst_status; void* embedded_proc_type; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {scalar_t__ idi_vaddr; } ;
struct bnxt_softc {TYPE_1__ hwrm_cmd_resp; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  HWRM_FW_RESET ; 
 int /*<<< orphan*/  MPASS (void**) ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_fw_reset_input*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_fw_reset_input*,int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_fw_reset(struct bnxt_softc *softc, uint8_t processor,
    uint8_t *selfreset)
{
	struct hwrm_fw_reset_input req = {0};
	struct hwrm_fw_reset_output *resp =
	    (void *)softc->hwrm_cmd_resp.idi_vaddr;
	int rc;

	MPASS(selfreset);

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_FW_RESET);
	req.embedded_proc_type = processor;
	req.selfrst_status = *selfreset;

	BNXT_HWRM_LOCK(softc);
	rc = _hwrm_send_message(softc, &req, sizeof(req));
	if (rc)
		goto exit;
	*selfreset = resp->selfrst_status;

exit:
	BNXT_HWRM_UNLOCK(softc);
	return rc;
}