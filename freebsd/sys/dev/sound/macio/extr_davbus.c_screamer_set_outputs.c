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
struct davbus_softc {int output_mask; int device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  SCREAMER_CODEC_ADDR1 ; 
 int SCREAMER_MUTE_HEADPHONES ; 
 int SCREAMER_MUTE_SPEAKER ; 
 int SCREAMER_PROG_OUTPUT0 ; 
 int SCREAMER_PROG_OUTPUT1 ; 
 int /*<<< orphan*/  screamer_write_locked (struct davbus_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
screamer_set_outputs(struct davbus_softc *d, u_int mask)
{
	u_int 	x;

	if (mask == d->output_mask) {
		return;
	}

	x = SCREAMER_MUTE_SPEAKER | SCREAMER_MUTE_HEADPHONES;

	DPRINTF(("Enabled outputs: "));

	if (mask & (1 << 0)) {
		DPRINTF(("SPEAKER "));
		x &= ~SCREAMER_MUTE_SPEAKER;
	}
	if (mask & (1 << 1)) {
		DPRINTF(("HEADPHONES "));
		x &= ~SCREAMER_MUTE_HEADPHONES;
	}

	DPRINTF(("\n"));

	if (d->device_id == 5 || d->device_id == 11) {
		DPRINTF(("Enabling programmable output.\n"));
		x |= SCREAMER_PROG_OUTPUT0;
	}
	if (d->device_id == 8 || d->device_id == 11) {
		x &= ~SCREAMER_MUTE_SPEAKER;

		if (mask & (1 << 0))
			x |= SCREAMER_PROG_OUTPUT1; /* enable speaker. */
	}

	screamer_write_locked(d, SCREAMER_CODEC_ADDR1, x);
	d->output_mask = mask;
}