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
typedef  int uint32_t ;
struct mtk_pin_group {int funcnum; int mask; int offset; int /*<<< orphan*/  sysc_reg; TYPE_1__* functions; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int value; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ENOENT ; 
 int mtk_sysctl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_sysctl_set (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
mtk_pinctrl_process_entry(device_t dev, struct mtk_pin_group *table,
    const char *group, char *func)
{
	uint32_t val;
	int found = 0, i, j;

	for (i = 0; table[i].name != NULL; i++) {
                if (strcmp(table[i].name, group) == 0) {
			found = 1;
                        break;
		}
        }

	if (!found)
		return (ENOENT);

        for (j = 0; j < table[i].funcnum; j++) {
                if (strcmp(table[i].functions[j].name, func) == 0) {
                        val = mtk_sysctl_get(table[i].sysc_reg);
                        val &= ~(table[i].mask << table[i].offset);
                        val |= (table[i].functions[j].value << table[i].offset);
                        mtk_sysctl_set(table[i].sysc_reg, val);
                        return (0);
		}
	}

	return (ENOENT);
}