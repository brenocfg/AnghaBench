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
struct iwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IWN_CLRBITS (struct iwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWN_GP_CNTRL ; 
 int /*<<< orphan*/  IWN_GP_CNTRL_INIT_DONE ; 
 int /*<<< orphan*/  IWN_RESET ; 
 int /*<<< orphan*/  IWN_RESET_SW ; 
 int /*<<< orphan*/  IWN_SETBITS (struct iwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwn_apm_stop_master (struct iwn_softc*) ; 

__attribute__((used)) static void
iwn_apm_stop(struct iwn_softc *sc)
{
	iwn_apm_stop_master(sc);

	/* Reset the entire device. */
	IWN_SETBITS(sc, IWN_RESET, IWN_RESET_SW);
	DELAY(10);
	/* Clear "initialization complete" bit. */
	IWN_CLRBITS(sc, IWN_GP_CNTRL, IWN_GP_CNTRL_INIT_DONE);
}