#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  modal_header_5g; int /*<<< orphan*/  modal_header_2g; } ;
typedef  TYPE_1__ ar9300_eeprom_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  eeprom_9300_base_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeprom_9300_hdr_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeprom_9300_modal_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_eeprom_dump (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  usage (char**) ; 

int
main(int argc, char *argv[])
{
	uint16_t *eep = NULL;
	const ar9300_eeprom_t *ee;

	eep = calloc(4096, sizeof(int16_t));

	if (argc < 2)
		usage(argv);

	load_eeprom_dump(argv[1], eep);
	ee = (ar9300_eeprom_t *) eep;

	eeprom_9300_hdr_print(eep);
	eeprom_9300_base_print(eep);

	printf("\n2GHz modal:\n");
	eeprom_9300_modal_print(&ee->modal_header_2g);

	printf("\n5GHz modal:\n");
	eeprom_9300_modal_print(&ee->modal_header_5g);

	free(eep);
	exit(0);
}