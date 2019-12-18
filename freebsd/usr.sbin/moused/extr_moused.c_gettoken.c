#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ symtab_t ;

/* Variables and functions */
 scalar_t__ strncmp (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static symtab_t *
gettoken(symtab_t *tab, const char *s, int len)
{
    int i;

    for (i = 0; tab[i].name != NULL; ++i) {
	if (strncmp(tab[i].name, s, len) == 0)
	    break;
    }
    return (&tab[i]);
}