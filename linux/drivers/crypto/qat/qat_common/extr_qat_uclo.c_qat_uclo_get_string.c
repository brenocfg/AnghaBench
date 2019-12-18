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
struct icp_qat_uof_strtable {unsigned int table_len; scalar_t__ strings; } ;

/* Variables and functions */

__attribute__((used)) static char *qat_uclo_get_string(struct icp_qat_uof_strtable *str_table,
				 unsigned int str_offset)
{
	if ((!str_table->table_len) || (str_offset > str_table->table_len))
		return NULL;
	return (char *)(((uintptr_t)(str_table->strings)) + str_offset);
}