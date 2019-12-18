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
struct mtkswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPA_ALL_AUTO ; 
 int /*<<< orphan*/  MTKSWITCH_FPA ; 
 int /*<<< orphan*/  MTKSWITCH_WRITE (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtkswitch_hw_setup(struct mtkswitch_softc *sc)
{

	/*
	 * TODO: parse the device tree and see if we need to configure
	 *       ports, etc. differently. For now we fallback to defaults.
	 */

	/* Called early and hence unlocked */
	/* Set ports 0-4 to auto negotiation */
	MTKSWITCH_WRITE(sc, MTKSWITCH_FPA, FPA_ALL_AUTO);

	return (0);
}