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
struct smc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_LOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  SMC_UNLOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  smc_init_locked (struct smc_softc*) ; 

__attribute__((used)) static void
smc_init(void *context)
{
	struct smc_softc	*sc;

	sc = (struct smc_softc *)context;
	SMC_LOCK(sc);
	smc_init_locked(sc);
	SMC_UNLOCK(sc);
}