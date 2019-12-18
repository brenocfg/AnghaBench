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
struct workspaces_json_params {TYPE_1__* workspaces_walk; int /*<<< orphan*/ * cur_key; } ;
typedef  int /*<<< orphan*/  rect ;
struct TYPE_3__ {int num; int /*<<< orphan*/ * output; int /*<<< orphan*/  rect; scalar_t__ urgent; scalar_t__ focused; scalar_t__ visible; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ i3_ws ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* smalloc (int) ; 

__attribute__((used)) static int workspaces_start_map_cb(void *params_) {
    struct workspaces_json_params *params = (struct workspaces_json_params *)params_;

    i3_ws *new_workspace = NULL;

    if (params->cur_key == NULL) {
        new_workspace = smalloc(sizeof(i3_ws));
        new_workspace->num = -1;
        new_workspace->name = NULL;
        new_workspace->visible = 0;
        new_workspace->focused = 0;
        new_workspace->urgent = 0;
        memset(&new_workspace->rect, 0, sizeof(rect));
        new_workspace->output = NULL;

        params->workspaces_walk = new_workspace;
        return 1;
    }

    return 1;
}