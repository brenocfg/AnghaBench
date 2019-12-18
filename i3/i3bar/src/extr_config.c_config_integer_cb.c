#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_5__ {long long input_code; } ;
typedef  TYPE_1__ binding_t ;
struct TYPE_6__ {long long tray_padding; long long ws_min_width; void* modifier; void* bar_height; int /*<<< orphan*/  bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,long long) ; 
 int /*<<< orphan*/  ELOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bindings ; 
 TYPE_3__ config ; 
 int /*<<< orphan*/  cur_key ; 
 scalar_t__ parsing_bindings ; 
 TYPE_1__* scalloc (int,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int config_integer_cb(void *params_, long long val) {
    if (parsing_bindings) {
        if (strcmp(cur_key, "input_code") == 0) {
            binding_t *binding = scalloc(1, sizeof(binding_t));
            binding->input_code = val;
            TAILQ_INSERT_TAIL(&(config.bindings), binding, bindings);

            return 1;
        }

        ELOG("Unknown key \"%s\" while parsing bar bindings.\n", cur_key);
        return 0;
    }

    if (!strcmp(cur_key, "bar_height")) {
        DLOG("bar_height = %lld", val);
        config.bar_height = (uint32_t)val;
        return 1;
    }

    if (!strcmp(cur_key, "tray_padding")) {
        DLOG("tray_padding = %lld\n", val);
        config.tray_padding = val;
        return 1;
    }

    if (!strcmp(cur_key, "modifier")) {
        DLOG("modifier = %lld\n", val);
        config.modifier = (uint32_t)val;
        return 1;
    }

    if (!strcmp(cur_key, "workspace_min_width")) {
        DLOG("workspace_min_width = %lld\n", val);
        config.ws_min_width = val;
        return 1;
    }

    return 0;
}