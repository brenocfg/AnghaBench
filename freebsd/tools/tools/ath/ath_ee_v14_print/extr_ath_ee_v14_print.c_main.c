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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  eeprom_v14_base_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeprom_v14_calfreqpiers_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeprom_v14_ctl_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeprom_v14_custdata_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeprom_v14_modal_print (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eeprom_v14_print_edges (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeprom_v14_print_targets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_eeprom_dump (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  usage (char**) ; 

int
main(int argc, char *argv[])
{
	uint16_t *eep = NULL;
	eep = calloc(4096, sizeof(int16_t));

	if (argc < 2)
		usage(argv);

	load_eeprom_dump(argv[1], eep);

	eeprom_v14_base_print(eep);
	eeprom_v14_custdata_print(eep);

	/* 2.4ghz */
	printf("\n2.4ghz:\n");
	eeprom_v14_modal_print(eep, 1);
	/* 5ghz */
	printf("\n5ghz:\n");
	eeprom_v14_modal_print(eep, 0);
	printf("\n");

	eeprom_v14_calfreqpiers_print(eep);
	printf("\n");

	eeprom_v14_print_targets(eep);
	printf("\n");

	eeprom_v14_ctl_print(eep);
	printf("\n");

	eeprom_v14_print_edges(eep);
	printf("\n");

	free(eep);
	exit(0);
}