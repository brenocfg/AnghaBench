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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void help_sweep(FILE * out, int detail)
{
	fprintf(out, "sweep [on|off]\n");
	if (detail) {
		fprintf(out, "enable or disable sweeping\n");
		fprintf(out, "   [on] sweep normally\n");
		fprintf(out, "   [off] inhibit all sweeping\n");
	}
}