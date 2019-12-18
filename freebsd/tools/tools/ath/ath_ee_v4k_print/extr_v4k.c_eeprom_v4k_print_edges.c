#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int ee_numCtls; TYPE_1__* ee_rdEdgesPower; } ;
struct TYPE_3__ {int rdEdge; int flag; scalar_t__ twice_rdEdgePower; } ;
typedef  TYPE_2__ HAL_EEPROM_v4k ;

/* Variables and functions */
 int NUM_EDGES ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
eeprom_v4k_print_edges(uint16_t *buf)
{
	HAL_EEPROM_v4k *eep = (HAL_EEPROM_v4k *) buf;
	int i;

	printf("| eeNumCtls: %d\n", eep->ee_numCtls);
	for (i = 0; i < NUM_EDGES*eep->ee_numCtls; i++) {
		/* XXX is flag 8 or 32 bits? */
		printf("|  edge %2d/%2d: rdEdge: %5d EdgePower: %.2f dBm Flag: 0x%.8x\n",
			i / NUM_EDGES, i % NUM_EDGES,
			eep->ee_rdEdgesPower[i].rdEdge,
			(float) eep->ee_rdEdgesPower[i].twice_rdEdgePower / 2.0,
			eep->ee_rdEdgesPower[i].flag);

		if (i % NUM_EDGES == (NUM_EDGES -1))
			printf("|\n");
	}
}