#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ti_sysc_module_data {int /*<<< orphan*/  name; } ;
struct omap_hwmod_reset {int /*<<< orphan*/  reset; int /*<<< orphan*/  len; int /*<<< orphan*/  match; } ;
struct omap_hwmod {TYPE_1__* class; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
omap_hwmod_init_reset_quirk(struct device *dev, struct omap_hwmod *oh,
			    const struct ti_sysc_module_data *data,
			    const struct omap_hwmod_reset *quirks,
			    int quirks_sz)
{
	const struct omap_hwmod_reset *quirk;
	int i;

	for (i = 0; i < quirks_sz; i++) {
		quirk = &quirks[i];
		if (!strncmp(data->name, quirk->match, quirk->len)) {
			oh->class->reset = quirk->reset;

			return;
		}
	}
}