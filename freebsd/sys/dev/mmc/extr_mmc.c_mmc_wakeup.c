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
struct mmc_softc {int dummy; } ;
struct mmc_request {int /*<<< orphan*/  flags; scalar_t__ done_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_LOCK (struct mmc_softc*) ; 
 int /*<<< orphan*/  MMC_REQ_DONE ; 
 int /*<<< orphan*/  MMC_UNLOCK (struct mmc_softc*) ; 
 int /*<<< orphan*/  wakeup (struct mmc_request*) ; 

__attribute__((used)) static void
mmc_wakeup(struct mmc_request *req)
{
	struct mmc_softc *sc;

	sc = (struct mmc_softc *)req->done_data;
	MMC_LOCK(sc);
	req->flags |= MMC_REQ_DONE;
	MMC_UNLOCK(sc);
	wakeup(req);
}