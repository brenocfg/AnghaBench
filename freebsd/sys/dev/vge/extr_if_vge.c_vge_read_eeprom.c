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
typedef  int /*<<< orphan*/  uint16_t ;
struct vge_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_1 (struct vge_softc*,scalar_t__) ; 
 int ETHER_ADDR_LEN ; 
 scalar_t__ VGE_PAR0 ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vge_eeprom_getword (struct vge_softc*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vge_read_eeprom(struct vge_softc *sc, caddr_t dest, int off, int cnt, int swap)
{
	int i;
#ifdef VGE_EEPROM
	uint16_t word = 0, *ptr;

	for (i = 0; i < cnt; i++) {
		vge_eeprom_getword(sc, off + i, &word);
		ptr = (uint16_t *)(dest + (i * 2));
		if (swap)
			*ptr = ntohs(word);
		else
			*ptr = word;
	}
#else
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		dest[i] = CSR_READ_1(sc, VGE_PAR0 + i);
#endif
}