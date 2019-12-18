#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* name; int /*<<< orphan*/  marks_head; int /*<<< orphan*/  swallow_head; struct TYPE_11__* deco_render_params; } ;
typedef  TYPE_1__ mark_t ;
typedef  TYPE_1__ Match ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_cons ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  marks ; 
 int /*<<< orphan*/  match_free (TYPE_1__*) ; 
 int /*<<< orphan*/  matches ; 

void con_free(Con *con) {
    free(con->name);
    FREE(con->deco_render_params);
    TAILQ_REMOVE(&all_cons, con, all_cons);
    while (!TAILQ_EMPTY(&(con->swallow_head))) {
        Match *match = TAILQ_FIRST(&(con->swallow_head));
        TAILQ_REMOVE(&(con->swallow_head), match, matches);
        match_free(match);
        free(match);
    }
    while (!TAILQ_EMPTY(&(con->marks_head))) {
        mark_t *mark = TAILQ_FIRST(&(con->marks_head));
        TAILQ_REMOVE(&(con->marks_head), mark, marks);
        FREE(mark->name);
        FREE(mark);
    }
    free(con);
    DLOG("con %p freed\n", con);
}