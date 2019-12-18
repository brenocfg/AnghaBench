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
struct name_table {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int print_mask_int (int /*<<< orphan*/ *,struct name_table*,int,int*) ; 

__attribute__((used)) static bool
print_mask_0(FILE *fp, struct name_table *table, int val, int *rem)
{

	if (val == 0) {
		fputs("0", fp);
		if (rem != NULL)
			*rem = 0;
		return (true);
	}
	return (print_mask_int(fp, table, val, rem));
}