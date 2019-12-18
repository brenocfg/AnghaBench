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
typedef  int /*<<< orphan*/  u_short ;
struct fxp_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fxp_eeprom_getword (struct fxp_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fxp_read_eeprom(struct fxp_softc *sc, u_short *data, int offset, int words)
{
	int i;

	for (i = 0; i < words; i++)
		data[i] = fxp_eeprom_getword(sc, offset + i, 0);
}