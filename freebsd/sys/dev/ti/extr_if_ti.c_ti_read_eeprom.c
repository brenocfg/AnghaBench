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
typedef  int /*<<< orphan*/  uint8_t ;
struct ti_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int ti_eeprom_getbyte (struct ti_softc*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ti_read_eeprom(struct ti_softc *sc, caddr_t dest, int off, int cnt)
{
	int err = 0, i;
	uint8_t byte = 0;

	for (i = 0; i < cnt; i++) {
		err = ti_eeprom_getbyte(sc, off + i, &byte);
		if (err)
			break;
		*(dest + i) = byte;
	}

	return (err ? 1 : 0);
}