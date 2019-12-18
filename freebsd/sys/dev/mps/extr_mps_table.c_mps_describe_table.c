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
typedef  scalar_t__ u_int ;
struct mps_table_lookup {char* string; scalar_t__ code; } ;

/* Variables and functions */

char *
mps_describe_table(struct mps_table_lookup *table, u_int code)
{
	int i;

	for (i = 0; table[i].string != NULL; i++) {
		if (table[i].code == code)
			return(table[i].string);
	}
	return(table[i+1].string);
}