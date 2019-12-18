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
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; } ;
struct mrsas_mfi_cmd {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct TYPE_7__ {TYPE_2__ addr; } ;
typedef  TYPE_3__ MRSAS_REQUEST_DESCRIPTOR_UNION ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* mrsas_build_mpt_cmd (struct mrsas_softc*,struct mrsas_mfi_cmd*) ; 
 int /*<<< orphan*/  mrsas_fire_cmd (struct mrsas_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mrsas_issue_dcmd(struct mrsas_softc *sc, struct mrsas_mfi_cmd *cmd)
{
	MRSAS_REQUEST_DESCRIPTOR_UNION *req_desc;

	req_desc = mrsas_build_mpt_cmd(sc, cmd);
	if (!req_desc) {
		device_printf(sc->mrsas_dev, "Cannot build MPT cmd.\n");
		return (1);
	}
	mrsas_fire_cmd(sc, req_desc->addr.u.low, req_desc->addr.u.high);

	return (0);
}