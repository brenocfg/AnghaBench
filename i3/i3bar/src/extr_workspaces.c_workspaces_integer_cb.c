#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct workspaces_json_params {int /*<<< orphan*/  cur_key; TYPE_2__* workspaces_walk; } ;
struct TYPE_3__ {int x; int y; int w; int h; } ;
struct TYPE_4__ {int num; TYPE_1__ rect; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int workspaces_integer_cb(void *params_, long long val) {
    struct workspaces_json_params *params = (struct workspaces_json_params *)params_;

    if (!strcmp(params->cur_key, "num")) {
        params->workspaces_walk->num = (int)val;
        FREE(params->cur_key);
        return 1;
    }

    if (!strcmp(params->cur_key, "x")) {
        params->workspaces_walk->rect.x = (int)val;
        FREE(params->cur_key);
        return 1;
    }

    if (!strcmp(params->cur_key, "y")) {
        params->workspaces_walk->rect.y = (int)val;
        FREE(params->cur_key);
        return 1;
    }

    if (!strcmp(params->cur_key, "width")) {
        params->workspaces_walk->rect.w = (int)val;
        FREE(params->cur_key);
        return 1;
    }

    if (!strcmp(params->cur_key, "height")) {
        params->workspaces_walk->rect.h = (int)val;
        FREE(params->cur_key);
        return 1;
    }

    FREE(params->cur_key);
    return 0;
}