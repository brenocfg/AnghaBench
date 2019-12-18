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
struct ahci_led {int num; int /*<<< orphan*/  dev; } ;
struct ahci_enclosure {int** status; } ;

/* Variables and functions */
 int AHCI_NUM_LEDS ; 
 int SESCTL_RQSFLT ; 
 int SESCTL_RQSID ; 
 int /*<<< orphan*/  ahci_em_setleds (int /*<<< orphan*/ ,int) ; 
 struct ahci_enclosure* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahci_em_led(void *priv, int onoff)
{
	struct ahci_led *led;
	struct ahci_enclosure *enc;
	int c, l;

	led = (struct ahci_led *)priv;
	enc = device_get_softc(led->dev);
	c = led->num / AHCI_NUM_LEDS;
	l = led->num % AHCI_NUM_LEDS;

	if (l == 0) {
		if (onoff)
			enc->status[c][2] |= 0x80;
		else
			enc->status[c][2] &= ~0x80;
	} else if (l == 1) {
		if (onoff)
			enc->status[c][2] |= SESCTL_RQSID;
		else
			enc->status[c][2] &= ~SESCTL_RQSID;
	} else if (l == 2) {
		if (onoff)
			enc->status[c][3] |= SESCTL_RQSFLT;
		else
			enc->status[c][3] &= SESCTL_RQSFLT;
	}
	ahci_em_setleds(led->dev, c);
}