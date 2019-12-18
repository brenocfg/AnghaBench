#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int major; scalar_t__ minor; int size; } ;
typedef  TYPE_1__ pir_table_t ;

/* Variables and functions */
 int PIR_SIZE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (unsigned char*,char*,int) ; 

pir_table_t *
find_pir_table(unsigned char *base)
{
	unsigned int csum = 0;
	unsigned char *p, *pend;
	pir_table_t *pir = NULL;

	/*
	 * From Microsoft's PCI IRQ Routing Table Specification 1.0:
	 *
	 * The PCI IRQ Routing Table can be detected by searching the
	 * system memory from F0000h to FFFFFh at every 16-byte boundary
	 * for the PCI IRQ routing signature ("$PIR").
	 */
	pend = base + PIR_SIZE;
	for (p = base; p < pend; p += 16) {
		if (strncmp(p, "$PIR", 4) == 0) {
			pir = (pir_table_t *)p;
			break;
		}
	}

	/*
	 * Now validate the table:
	 * Version: Must be 1.0.
	 * Table size: Must be larger than 32 and must be a multiple of 16.
	 * Checksum: The entire structure's checksum must be 0.
	 */
	if (pir && (pir->major == 1) && (pir->minor == 0) &&
	    (pir->size > 32) && ((pir->size % 16) == 0)) {
		p = (unsigned char *)pir;
		pend = p + pir->size;

		while (p < pend)
			csum += *p++;

		if ((csum % 256) != 0)
			fprintf(stderr,
			    "WARNING: PIR table checksum is invalid.\n");
	}

	return ((pir_table_t *)pir);
}