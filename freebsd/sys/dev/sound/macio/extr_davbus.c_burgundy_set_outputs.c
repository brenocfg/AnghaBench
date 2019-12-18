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
struct davbus_softc {int output_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BURGUNDY_MUTE_REG ; 
 int BURGUNDY_P14L_EN ; 
 int BURGUNDY_P14R_EN ; 
 int BURGUNDY_P17M_EN ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  burgundy_write_locked (struct davbus_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
burgundy_set_outputs(struct davbus_softc *d, u_int mask)
{
	u_int	x = 0;

	if (mask == d->output_mask)
		return;

	/*
	 *	Bordeaux card wirings:
	 *		Port 15:	RCA out
	 *		Port 16:	Minijack out
	 *		Port 17:	Internal speaker
	 *
	 *	B&W G3 wirings:
	 *		Port 14:	Minijack out
	 *		Port 17:	Internal speaker
	 */

	DPRINTF(("Enabled outputs:"));
	if (mask & (1 << 0)) {
		DPRINTF((" SPEAKER"));
		x |= BURGUNDY_P17M_EN;
	}
	if (mask & (1 << 1)) {
		DPRINTF((" HEADPHONES"));
		x |= BURGUNDY_P14L_EN | BURGUNDY_P14R_EN;	
	}
	DPRINTF(("\n"));

	burgundy_write_locked(d, BURGUNDY_MUTE_REG, x);
	d->output_mask = mask;
}