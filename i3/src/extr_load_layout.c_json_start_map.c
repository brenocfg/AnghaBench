#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  dock; } ;
struct TYPE_11__ {struct TYPE_11__* parent; int /*<<< orphan*/ * name; int /*<<< orphan*/  swallow_head; } ;
typedef  int /*<<< orphan*/  Match ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  LOG (char*,...) ; 
 int /*<<< orphan*/  M_DONTCHECK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* con_get_workspace (TYPE_1__*) ; 
 TYPE_1__* con_new_skeleton (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* current_swallow ; 
 TYPE_1__* incomplete ; 
 TYPE_1__* json_node ; 
 scalar_t__ last_key ; 
 int /*<<< orphan*/  match_init (TYPE_2__*) ; 
 int /*<<< orphan*/  matches ; 
 int /*<<< orphan*/  parsing_deco_rect ; 
 int /*<<< orphan*/  parsing_gaps ; 
 int /*<<< orphan*/  parsing_geometry ; 
 int /*<<< orphan*/  parsing_rect ; 
 scalar_t__ parsing_swallows ; 
 int /*<<< orphan*/  parsing_window_rect ; 
 TYPE_2__* smalloc (int) ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 
 int swallow_is_empty ; 

__attribute__((used)) static int json_start_map(void *ctx) {
    LOG("start of map, last_key = %s\n", last_key);
    if (parsing_swallows) {
        LOG("creating new swallow\n");
        current_swallow = smalloc(sizeof(Match));
        match_init(current_swallow);
        current_swallow->dock = M_DONTCHECK;
        TAILQ_INSERT_TAIL(&(json_node->swallow_head), current_swallow, matches);
        swallow_is_empty = true;
    } else {
        if (!parsing_rect && !parsing_deco_rect && !parsing_window_rect && !parsing_geometry && !parsing_gaps) {
            if (last_key && strcasecmp(last_key, "floating_nodes") == 0) {
                DLOG("New floating_node\n");
                Con *ws = con_get_workspace(json_node);
                json_node = con_new_skeleton(NULL, NULL);
                json_node->name = NULL;
                json_node->parent = ws;
                DLOG("Parent is workspace = %p\n", ws);
            } else {
                Con *parent = json_node;
                json_node = con_new_skeleton(NULL, NULL);
                json_node->name = NULL;
                json_node->parent = parent;
            }
            /* json_node is incomplete and should be removed if parsing fails */
            incomplete++;
            DLOG("incomplete = %d\n", incomplete);
        }
    }
    return 1;
}