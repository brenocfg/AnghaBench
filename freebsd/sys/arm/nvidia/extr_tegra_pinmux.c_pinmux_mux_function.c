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
struct tegra_mux {int /*<<< orphan*/ * functions; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pinmux_mux_function(const struct tegra_mux *mux, char *fnc_name)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (strcmp(fnc_name, mux->functions[i]) == 0)
			return 	(i);
	}
	return (-1);
}