#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct outputs_json_params {int in_rect; TYPE_4__* outputs_walk; TYPE_4__* cur_key; } ;
struct TYPE_7__ {int /*<<< orphan*/  rect; int /*<<< orphan*/  ws; scalar_t__ primary; int /*<<< orphan*/  active; } ;
typedef  TYPE_1__ i3_output ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  rect; int /*<<< orphan*/  ws; scalar_t__ primary; int /*<<< orphan*/  active; } ;
struct TYPE_8__ {int num_outputs; char** outputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,char*) ; 
 int /*<<< orphan*/  FREE (TYPE_4__*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_output (TYPE_4__*) ; 
 TYPE_3__ config ; 
 TYPE_1__* get_output_by_name (char*) ; 
 int /*<<< orphan*/  outputs ; 
 int /*<<< orphan*/  slist ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static int outputs_end_map_cb(void *params_) {
    struct outputs_json_params *params = (struct outputs_json_params *)params_;
    if (params->in_rect) {
        params->in_rect = false;
        /* Ignore the end of a rect */
        return 1;
    }

    /* See if we actually handle that output */
    if (config.num_outputs > 0) {
        bool handle_output = false;
        for (int c = 0; c < config.num_outputs; c++) {
            if (strcasecmp(params->outputs_walk->name, config.outputs[c]) == 0 ||
                (strcasecmp(config.outputs[c], "primary") == 0 &&
                 params->outputs_walk->primary)) {
                handle_output = true;
                break;
            }
        }
        if (!handle_output) {
            DLOG("Ignoring output \"%s\", not configured to handle it.\n",
                 params->outputs_walk->name);
            clear_output(params->outputs_walk);
            FREE(params->outputs_walk);
            FREE(params->cur_key);
            return 1;
        }
    }

    i3_output *target = get_output_by_name(params->outputs_walk->name);

    if (target == NULL) {
        SLIST_INSERT_HEAD(outputs, params->outputs_walk, slist);
    } else {
        target->active = params->outputs_walk->active;
        target->primary = params->outputs_walk->primary;
        target->ws = params->outputs_walk->ws;
        target->rect = params->outputs_walk->rect;

        clear_output(params->outputs_walk);
        FREE(params->outputs_walk);
    }
    return 1;
}