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
struct TYPE_4__ {scalar_t__ section; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ CONF_VALUE ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int conf_value_cmp(const CONF_VALUE *a, const CONF_VALUE *b)
{
    int i;

    if (a->section != b->section) {
        i = strcmp(a->section, b->section);
        if (i)
            return i;
    }

    if ((a->name != NULL) && (b->name != NULL)) {
        i = strcmp(a->name, b->name);
        return i;
    } else if (a->name == b->name)
        return 0;
    else
        return ((a->name == NULL) ? -1 : 1);
}