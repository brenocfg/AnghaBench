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
typedef  int /*<<< orphan*/  uintmax_t ;
struct name_table {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 char* lookup_value (struct name_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
print_value(FILE *fp, struct name_table *table, uintmax_t val)
{
	const char *str;

	str = lookup_value(table, val);
	if (str != NULL) {
		fputs(str, fp);
		return (true);
	}
	return (false);
}