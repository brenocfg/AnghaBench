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
struct data_header {scalar_t__ type; scalar_t__ id; int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ DATA_HEADER_EEPROM ; 
 scalar_t__ DATA_HEADER_ID_CAL ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  ofname ; 
 int write_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_eeprom(struct data_header **data_table, int cnt)
{
	int ret = EXIT_FAILURE;

	for (int i = 0; i < cnt; i++) {
		if (data_table[i]->type == DATA_HEADER_EEPROM
		    && data_table[i]->id == DATA_HEADER_ID_CAL) {
			ret =
			    write_file(ofname, data_table[i]->data,
				       data_table[i]->length);
			break;
		}

	}

	return ret;
}