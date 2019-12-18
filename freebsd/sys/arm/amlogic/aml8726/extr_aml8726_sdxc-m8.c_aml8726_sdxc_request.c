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
struct mmc_request {int /*<<< orphan*/  (* done ) (struct mmc_request*) ;TYPE_1__* cmd; } ;
struct aml8726_sdxc_softc {int /*<<< orphan*/ * cmd; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_SDXC_LOCK (struct aml8726_sdxc_softc*) ; 
 int /*<<< orphan*/  AML_SDXC_UNLOCK (struct aml8726_sdxc_softc*) ; 
 int EBUSY ; 
 int MMC_ERR_NONE ; 
 int aml8726_sdxc_start_command (struct aml8726_sdxc_softc*,TYPE_1__*) ; 
 struct aml8726_sdxc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mmc_request*) ; 

__attribute__((used)) static int
aml8726_sdxc_request(device_t bus, device_t child, struct mmc_request *req)
{
	struct aml8726_sdxc_softc *sc = device_get_softc(bus);
	int mmc_error;

	AML_SDXC_LOCK(sc);

	if (sc->cmd != NULL) {
		AML_SDXC_UNLOCK(sc);
		return (EBUSY);
	}

	mmc_error = aml8726_sdxc_start_command(sc, req->cmd);

	AML_SDXC_UNLOCK(sc);

	/* Execute the callback after dropping the lock. */
	if (mmc_error != MMC_ERR_NONE) {
		req->cmd->error = mmc_error;
		req->done(req);
	}

	return (0);
}