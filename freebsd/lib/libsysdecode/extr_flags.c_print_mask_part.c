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
struct name_table {int val; int /*<<< orphan*/ * str; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_mask_part(FILE *fp, struct name_table *table, uintmax_t *valp,
    bool *printed)
{
	uintmax_t rem;

	rem = *valp;
	for (; table->str != NULL; table++) {
		if ((table->val & rem) == table->val) {
			/*
			 * Only print a zero mask if the raw value is
			 * zero.
			 */
			if (table->val == 0 && *valp != 0)
				continue;
			fprintf(fp, "%s%s", *printed ? "|" : "", table->str);
			*printed = true;
			rem &= ~table->val;
		}
	}

	*valp = rem;
}