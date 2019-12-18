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

__attribute__((used)) static void
mtkswitch_port_init(struct mtkswitch_softc *sc, int port)
{
	/* Called early and hence unlocked */
	/* Do nothing - ports are set to auto negotiation in hw_setup */
}