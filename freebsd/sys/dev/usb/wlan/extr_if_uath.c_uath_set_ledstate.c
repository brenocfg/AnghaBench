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
struct uath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct uath_softc*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  UATH_DEBUG_LED ; 
 int /*<<< orphan*/  WDCMSG_SET_LED_STATE ; 
 int htobe32 (int) ; 
 int uath_cmd_write (struct uath_softc*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_set_ledstate(struct uath_softc *sc, int connected)
{

	DPRINTF(sc, UATH_DEBUG_LED,
	    "set led state %sconnected\n", connected ? "" : "!");
	connected = htobe32(connected);
	return uath_cmd_write(sc, WDCMSG_SET_LED_STATE,
	     &connected, sizeof connected, 0);
}