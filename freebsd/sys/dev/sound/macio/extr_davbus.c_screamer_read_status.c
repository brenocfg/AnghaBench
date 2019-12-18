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
typedef  int u_int ;
struct davbus_softc {int device_id; } ;

/* Variables and functions */

__attribute__((used)) static u_int
screamer_read_status(struct davbus_softc *d, u_int status)
{
	int 	headphones;

	switch (d->device_id) {
	case 5: /* Sawtooth */
		headphones = (status & 0x4);
		break;

	case 8:
	case 11: /* iMac DV */
		/* The iMac DV has 2 headphone outputs. */
		headphones = (status & 0x7);
		break;

	default:
		headphones = (status & 0x8);
	}

	if (headphones)
		return (1 << 1);
	else
		return (1 << 0);
}