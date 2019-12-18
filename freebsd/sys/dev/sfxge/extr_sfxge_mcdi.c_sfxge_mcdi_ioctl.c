#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sfxge_mcdi {scalar_t__ state; } ;
struct sfxge_softc {struct sfxge_mcdi mcdi; int /*<<< orphan*/  enp; } ;
struct TYPE_9__ {int /*<<< orphan*/  cmd; scalar_t__ len; int /*<<< orphan*/  payload; int /*<<< orphan*/  rc; } ;
struct TYPE_10__ {TYPE_1__ mcdi; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
typedef  TYPE_3__ sfxge_ioc_t ;
struct TYPE_12__ {int enc_features; } ;
typedef  TYPE_4__ efx_nic_cfg_t ;
struct TYPE_13__ {scalar_t__ emr_out_length_used; int /*<<< orphan*/  emr_cmd; int /*<<< orphan*/  emr_rc; scalar_t__ emr_out_length; int /*<<< orphan*/ * emr_out_buf; scalar_t__ emr_in_length; int /*<<< orphan*/ * emr_in_buf; } ;
typedef  TYPE_5__ efx_mcdi_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFSYS_PROBE (int /*<<< orphan*/ ) ; 
 int EFX_FEATURE_MCDI ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  MC_CMD_REBOOT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ SFXGE_MCDI_MAX_PAYLOAD ; 
 scalar_t__ SFXGE_MCDI_UNINITIALIZED ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_4__* efx_nic_cfg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcdi_ioctl_mc_reboot ; 
 int /*<<< orphan*/  sfxge_mcdi_execute (struct sfxge_softc*,TYPE_5__*) ; 
 int /*<<< orphan*/  sfxge_schedule_reset (struct sfxge_softc*) ; 

int
sfxge_mcdi_ioctl(struct sfxge_softc *sc, sfxge_ioc_t *ip)
{
	const efx_nic_cfg_t *encp = efx_nic_cfg_get(sc->enp);
	struct sfxge_mcdi *mp = &(sc->mcdi);
	efx_mcdi_req_t emr;
	uint8_t *mcdibuf;
	int rc;

	if (mp->state == SFXGE_MCDI_UNINITIALIZED) {
		rc = ENODEV;
		goto fail1;
	}

	if (!(encp->enc_features & EFX_FEATURE_MCDI)) {
		rc = ENOTSUP;
		goto fail2;
	}

	if (ip->u.mcdi.len > SFXGE_MCDI_MAX_PAYLOAD) {
		rc = EINVAL;
		goto fail3;
	}

	mcdibuf = malloc(SFXGE_MCDI_MAX_PAYLOAD, M_TEMP, M_WAITOK | M_ZERO);
	if ((rc = copyin(ip->u.mcdi.payload, mcdibuf, ip->u.mcdi.len)) != 0) {
		goto fail5;
	}

	emr.emr_cmd = ip->u.mcdi.cmd;
	emr.emr_in_buf = mcdibuf;
	emr.emr_in_length = ip->u.mcdi.len;

	emr.emr_out_buf = mcdibuf;
	emr.emr_out_length = SFXGE_MCDI_MAX_PAYLOAD;

	sfxge_mcdi_execute(sc, &emr);

	ip->u.mcdi.rc = emr.emr_rc;
	ip->u.mcdi.cmd = emr.emr_cmd;
	ip->u.mcdi.len = emr.emr_out_length_used;
	if ((rc = copyout(mcdibuf, ip->u.mcdi.payload, ip->u.mcdi.len)) != 0) {
		goto fail6;
	}

	/*
	 * Helpfully trigger a device reset in response to an MCDI_CMD_REBOOT
	 * Both ports will see ->emt_exception callbacks on the next MCDI poll
	 */
	if (ip->u.mcdi.cmd == MC_CMD_REBOOT) {

		EFSYS_PROBE(mcdi_ioctl_mc_reboot);
		/* sfxge_t->s_state_lock held */
		(void) sfxge_schedule_reset(sc);
	}

	free(mcdibuf, M_TEMP);

	return (0);

fail6:
fail5:
	free(mcdibuf, M_TEMP);
fail3:
fail2:
fail1:
	return (rc);
}