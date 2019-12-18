#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int release; } ;
typedef  TYPE_1__ binding_t ;
struct TYPE_5__ {int disable_binding_mode_indicator; int disable_ws; int strip_ws_numbers; int strip_ws_name; int verbose; int /*<<< orphan*/  bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int) ; 
 int /*<<< orphan*/  ELOG (char*,...) ; 
 TYPE_1__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bindings_head ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  cur_key ; 
 scalar_t__ parsing_bindings ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int config_boolean_cb(void *params_, int val) {
    if (parsing_bindings) {
        if (strcmp(cur_key, "release") == 0) {
            binding_t *binding = TAILQ_LAST(&(config.bindings), bindings_head);
            if (binding == NULL) {
                ELOG("There is no binding to put the current command onto. This is a bug in i3.\n");
                return 0;
            }

            binding->release = val;
            return 1;
        }

        ELOG("Unknown key \"%s\" while parsing bar bindings.\n", cur_key);
    }

    if (!strcmp(cur_key, "binding_mode_indicator")) {
        DLOG("binding_mode_indicator = %d\n", val);
        config.disable_binding_mode_indicator = !val;
        return 1;
    }

    if (!strcmp(cur_key, "workspace_buttons")) {
        DLOG("workspace_buttons = %d\n", val);
        config.disable_ws = !val;
        return 1;
    }

    if (!strcmp(cur_key, "strip_workspace_numbers")) {
        DLOG("strip_workspace_numbers = %d\n", val);
        config.strip_ws_numbers = val;
        return 1;
    }

    if (!strcmp(cur_key, "strip_workspace_name")) {
        DLOG("strip_workspace_name = %d\n", val);
        config.strip_ws_name = val;
        return 1;
    }

    if (!strcmp(cur_key, "verbose")) {
        if (!config.verbose) {
            DLOG("verbose = %d\n", val);
            config.verbose = val;
        }
        return 1;
    }

    return 0;
}