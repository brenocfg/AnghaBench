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
typedef  scalar_t__ uint8_t ;
struct ucom_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__) ; 
 int /*<<< orphan*/  UCOM_LS_RING ; 
 int /*<<< orphan*/  ucom_line_state (struct ucom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ucom_ring(struct ucom_softc *sc, uint8_t onoff)
{
	DPRINTF("onoff = %d\n", onoff);

	if (onoff)
		ucom_line_state(sc, UCOM_LS_RING, 0);
	else
		ucom_line_state(sc, 0, UCOM_LS_RING);
}