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
struct TYPE_4__ {scalar_t__ links; int /*<<< orphan*/  dso; } ;
typedef  TYPE_1__ CONF_MODULE ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_modules_finish () ; 
 int /*<<< orphan*/  module_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sk_CONF_MODULE_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_CONF_MODULE_free (int /*<<< orphan*/ *) ; 
 int sk_CONF_MODULE_num (int /*<<< orphan*/ *) ; 
 TYPE_1__* sk_CONF_MODULE_value (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * supported_modules ; 

void CONF_modules_unload(int all)
{
    int i;
    CONF_MODULE *md;
    CONF_modules_finish();
    /* unload modules in reverse order */
    for (i = sk_CONF_MODULE_num(supported_modules) - 1; i >= 0; i--) {
        md = sk_CONF_MODULE_value(supported_modules, i);
        /* If static or in use and 'all' not set ignore it */
        if (((md->links > 0) || !md->dso) && !all)
            continue;
        /* Since we're working in reverse this is OK */
        (void)sk_CONF_MODULE_delete(supported_modules, i);
        module_free(md);
    }
    if (sk_CONF_MODULE_num(supported_modules) == 0) {
        sk_CONF_MODULE_free(supported_modules);
        supported_modules = NULL;
    }
}