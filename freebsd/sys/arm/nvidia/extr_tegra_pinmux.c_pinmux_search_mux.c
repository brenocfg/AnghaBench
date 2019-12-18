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
struct tegra_mux {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int nitems (struct tegra_mux const*) ; 
 struct tegra_mux const* pin_mux_tbl ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct tegra_mux *
pinmux_search_mux(char *pin_name)
{
	int i;

	for (i = 0; i < nitems(pin_mux_tbl); i++) {
		if (strcmp(pin_name, pin_mux_tbl[i].name) == 0)
			return 	(&pin_mux_tbl[i]);
	}
	return (NULL);
}