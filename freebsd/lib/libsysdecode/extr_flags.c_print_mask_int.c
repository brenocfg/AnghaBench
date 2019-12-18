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
typedef  int uintmax_t ;
struct name_table {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  print_mask_part (int /*<<< orphan*/ *,struct name_table*,int*,int*) ; 

__attribute__((used)) static bool
print_mask_int(FILE *fp, struct name_table *table, int ival, int *rem)
{
	uintmax_t val;
	bool printed;

	printed = false;
	val = (unsigned)ival;
	print_mask_part(fp, table, &val, &printed);
	if (rem != NULL)
		*rem = val;
	return (printed);
}