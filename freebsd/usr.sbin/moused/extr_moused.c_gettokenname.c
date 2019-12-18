#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* name; int val; } ;
typedef  TYPE_1__ symtab_t ;

/* Variables and functions */

__attribute__((used)) static const char *
gettokenname(symtab_t *tab, int val)
{
    static const char unknown[] = "unknown";
    int i;

    for (i = 0; tab[i].name != NULL; ++i) {
	if (tab[i].val == val)
	    return (tab[i].name);
    }
    return (unknown);
}