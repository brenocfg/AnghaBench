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
typedef  size_t u_int32_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const) ; 

__attribute__((used)) static void
print_string(FILE *fp, const char *str, size_t len)
{
	u_int32_t i;

	if (len > 0) {
		for (i = 0; i < len; i++) {
			if (str[i] != '\0')
				fprintf(fp, "%c", str[i]);
		}
	}
}