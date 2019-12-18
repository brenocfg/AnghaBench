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
struct tegra_grp {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int nitems (struct tegra_grp const*) ; 
 struct tegra_grp const* pin_grp_tbl ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct tegra_grp *
pinmux_search_grp(char *grp_name)
{
	int i;

	for (i = 0; i < nitems(pin_grp_tbl); i++) {
		if (strcmp(grp_name, pin_grp_tbl[i].name) == 0)
			return 	(&pin_grp_tbl[i]);
	}
	return (NULL);
}