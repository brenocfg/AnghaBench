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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct hwrm_nvm_erase_dir_entry_input {int /*<<< orphan*/  dir_idx; int /*<<< orphan*/  member_0; } ;
struct bnxt_softc {int /*<<< orphan*/  hwrm_cmd_timeo; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_NVM_TIMEO ; 
 int /*<<< orphan*/  HWRM_NVM_ERASE_DIR_ENTRY ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_nvm_erase_dir_entry_input*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_nvm_erase_dir_entry_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_nvm_erase_dir_entry(struct bnxt_softc *softc, uint16_t index)
{
	struct hwrm_nvm_erase_dir_entry_input req = {0};
	uint32_t old_timeo;
	int rc;

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_NVM_ERASE_DIR_ENTRY);
	req.dir_idx = htole16(index);
	BNXT_HWRM_LOCK(softc);
	old_timeo = softc->hwrm_cmd_timeo;
	softc->hwrm_cmd_timeo = BNXT_NVM_TIMEO;
	rc = _hwrm_send_message(softc, &req, sizeof(req));
	softc->hwrm_cmd_timeo = old_timeo;
	BNXT_HWRM_UNLOCK(softc);
	return rc;
}