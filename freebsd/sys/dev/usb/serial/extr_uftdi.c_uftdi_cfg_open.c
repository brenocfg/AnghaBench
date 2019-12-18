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
struct ucom_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 

__attribute__((used)) static void
uftdi_cfg_open(struct ucom_softc *ucom)
{

	/*
	 * This do-nothing open routine exists for the sole purpose of this
	 * DPRINTF() so that you can see the point at which open gets called
	 * when debugging is enabled.
	 */
	DPRINTF("\n");
}