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

/* Variables and functions */
 int ceil (double) ; 
 double dpi ; 
 int /*<<< orphan*/ * root_screen ; 

int logical_px(const int logical) {
    if (root_screen == NULL) {
        /* Dpi info may not be available when parsing a config without an X
         * server, such as for config file validation. */
        return logical;
    }

    /* There are many misconfigurations out there, i.e. systems with screens
     * whose dpi is in fact higher than 96 dpi, but not significantly higher,
     * so software was never adapted. We could tell people to reconfigure their
     * systems to 96 dpi in order to get the behavior they expect/are used to,
     * but since we can easily detect this case in code, let’s do it for them.
     */
    if ((dpi / 96.0) < 1.25)
        return logical;
    return ceil((dpi / 96.0) * logical);
}