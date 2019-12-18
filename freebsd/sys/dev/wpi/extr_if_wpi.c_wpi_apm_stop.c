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
struct wpi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  WPI_CLRBITS (struct wpi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPI_GP_CNTRL ; 
 int /*<<< orphan*/  WPI_GP_CNTRL_INIT_DONE ; 
 int /*<<< orphan*/  WPI_RESET ; 
 int /*<<< orphan*/  WPI_RESET_SW ; 
 int /*<<< orphan*/  WPI_SETBITS (struct wpi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpi_apm_stop_master (struct wpi_softc*) ; 

__attribute__((used)) static void
wpi_apm_stop(struct wpi_softc *sc)
{
	wpi_apm_stop_master(sc);

	/* Reset the entire device. */
	WPI_SETBITS(sc, WPI_RESET, WPI_RESET_SW);
	DELAY(10);
	/* Clear "initialization complete" bit. */
	WPI_CLRBITS(sc, WPI_GP_CNTRL, WPI_GP_CNTRL_INIT_DONE);
}