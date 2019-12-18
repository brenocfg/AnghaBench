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
struct workspaces_json_params {int /*<<< orphan*/  cur_key; TYPE_1__* workspaces_walk; } ;
struct TYPE_2__ {int visible; int focused; int urgent; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int workspaces_boolean_cb(void *params_, int val) {
    struct workspaces_json_params *params = (struct workspaces_json_params *)params_;

    if (!strcmp(params->cur_key, "visible")) {
        params->workspaces_walk->visible = val;
        FREE(params->cur_key);
        return 1;
    }

    if (!strcmp(params->cur_key, "focused")) {
        params->workspaces_walk->focused = val;
        FREE(params->cur_key);
        return 1;
    }

    if (!strcmp(params->cur_key, "urgent")) {
        params->workspaces_walk->urgent = val;
        FREE(params->cur_key);
        return 1;
    }

    FREE(params->cur_key);

    return 0;
}