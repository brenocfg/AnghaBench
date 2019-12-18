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
typedef  int /*<<< orphan*/  layout_t ;

/* Variables and functions */
 int /*<<< orphan*/  L_DEFAULT ; 
 int /*<<< orphan*/  L_SPLITH ; 
 int /*<<< orphan*/  L_SPLITV ; 
 int /*<<< orphan*/  L_STACKED ; 
 int /*<<< orphan*/  L_TABBED ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

bool layout_from_name(const char *layout_str, layout_t *out) {
    if (strcmp(layout_str, "default") == 0) {
        *out = L_DEFAULT;
        return true;
    } else if (strcasecmp(layout_str, "stacked") == 0 ||
               strcasecmp(layout_str, "stacking") == 0) {
        *out = L_STACKED;
        return true;
    } else if (strcasecmp(layout_str, "tabbed") == 0) {
        *out = L_TABBED;
        return true;
    } else if (strcasecmp(layout_str, "splitv") == 0) {
        *out = L_SPLITV;
        return true;
    } else if (strcasecmp(layout_str, "splith") == 0) {
        *out = L_SPLITH;
        return true;
    }

    return false;
}