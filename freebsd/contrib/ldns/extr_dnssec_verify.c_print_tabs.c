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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
print_tabs(FILE *out, size_t nr, uint8_t *map, size_t treedepth)
{
	size_t i;
	for (i = 0; i < nr; i++) {
		if (i == nr - 1) {
			fprintf(out, "|---");
		} else if (map && i < treedepth && map[i] == 1) {
			fprintf(out, "|   ");
		} else {
			fprintf(out, "    ");
		}
	}
}