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
typedef  scalar_t__ st_data_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ST_CONTINUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 

__attribute__((used)) static int dump_tbl_entry(st_data_t key, st_data_t val, st_data_t arg)
{
	FILE *p_file = (FILE *) arg;
	char *p_key = (char *)key;
	char *p_val = (char *)val;

	fprintf(p_file, "%s %s\n\n", p_key, p_val);
	return ST_CONTINUE;
}