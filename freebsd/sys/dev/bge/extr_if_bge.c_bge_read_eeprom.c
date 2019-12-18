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
struct bge_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int bge_eeprom_getbyte (struct bge_softc*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bge_read_eeprom(struct bge_softc *sc, caddr_t dest, int off, int cnt)
{
	int i, error = 0;
	uint8_t byte = 0;

	for (i = 0; i < cnt; i++) {
		error = bge_eeprom_getbyte(sc, off + i, &byte);
		if (error)
			break;
		*(dest + i) = byte;
	}

	return (error ? 1 : 0);
}