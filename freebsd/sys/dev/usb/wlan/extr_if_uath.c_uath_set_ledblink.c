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
struct uath_cmd_ledblink {void* slowmode; void* blinkrate; void* ledmode; void* lednum; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct uath_softc*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  UATH_DEBUG_LED ; 
 int UATH_LED_LINK ; 
 int /*<<< orphan*/  WDCMSG_SET_LED_BLINK ; 
 void* htobe32 (int) ; 
 int uath_cmd_write (struct uath_softc*,int /*<<< orphan*/ ,struct uath_cmd_ledblink*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_set_ledblink(struct uath_softc *sc, int lednum, int ledmode,
	int blinkrate, int slowmode)
{
	struct uath_cmd_ledblink led;

	led.lednum = htobe32(lednum);
	led.ledmode = htobe32(ledmode);
	led.blinkrate = htobe32(blinkrate);
	led.slowmode = htobe32(slowmode);

	DPRINTF(sc, UATH_DEBUG_LED, "set %s led %s (blink)\n",
	    (lednum == UATH_LED_LINK) ? "link" : "activity",
	    ledmode ? "on" : "off");
	return uath_cmd_write(sc, WDCMSG_SET_LED_BLINK, &led, sizeof led, 0);
}