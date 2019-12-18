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
struct outputs_json_params {int /*<<< orphan*/  cur_key; TYPE_1__* outputs_walk; } ;
struct TYPE_2__ {int active; int primary; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int outputs_boolean_cb(void *params_, int val) {
    struct outputs_json_params *params = (struct outputs_json_params *)params_;

    if (!strcmp(params->cur_key, "active")) {
        params->outputs_walk->active = val;
        FREE(params->cur_key);
        return 1;
    }

    if (!strcmp(params->cur_key, "primary")) {
        params->outputs_walk->primary = val;
        FREE(params->cur_key);
        return 1;
    }

    return 0;
}