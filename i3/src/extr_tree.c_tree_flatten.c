#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ type; scalar_t__ layout; int /*<<< orphan*/  floating_head; int /*<<< orphan*/  nodes_head; int /*<<< orphan*/  focus_head; int /*<<< orphan*/  percent; struct TYPE_15__* parent; int /*<<< orphan*/  name; int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 scalar_t__ CT_CON ; 
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  DONT_KILL_WINDOW ; 
 scalar_t__ L_OUTPUT ; 
 scalar_t__ L_SPLITH ; 
 scalar_t__ L_SPLITV ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  con_is_split (TYPE_1__*) ; 
 scalar_t__ con_orientation (TYPE_1__*) ; 
 int /*<<< orphan*/  floating_windows ; 
 int /*<<< orphan*/  focused ; 
 int /*<<< orphan*/  nodes ; 
 int /*<<< orphan*/  tree_close_internal (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void tree_flatten(Con *con) {
    Con *current, *child, *parent = con->parent;
    DLOG("Checking if I can flatten con = %p / %s\n", con, con->name);

    /* We only consider normal containers without windows */
    if (con->type != CT_CON ||
        parent->layout == L_OUTPUT || /* con == "content" */
        con->window != NULL)
        goto recurse;

    /* Ensure it got only one child */
    child = TAILQ_FIRST(&(con->nodes_head));
    if (child == NULL || TAILQ_NEXT(child, nodes) != NULL)
        goto recurse;

    DLOG("child = %p, con = %p, parent = %p\n", child, con, parent);

    /* The child must have a different orientation than the con but the same as
     * the con’s parent to be redundant */
    if (!con_is_split(con) ||
        !con_is_split(child) ||
        (con->layout != L_SPLITH && con->layout != L_SPLITV) ||
        (child->layout != L_SPLITH && child->layout != L_SPLITV) ||
        con_orientation(con) == con_orientation(child) ||
        con_orientation(child) != con_orientation(parent))
        goto recurse;

    DLOG("Alright, I have to flatten this situation now. Stay calm.\n");
    /* 1: save focus */
    Con *focus_next = TAILQ_FIRST(&(child->focus_head));

    DLOG("detaching...\n");
    /* 2: re-attach the children to the parent before con */
    while (!TAILQ_EMPTY(&(child->nodes_head))) {
        current = TAILQ_FIRST(&(child->nodes_head));
        DLOG("detaching current=%p / %s\n", current, current->name);
        con_detach(current);
        DLOG("re-attaching\n");
        /* We don’t use con_attach() here because for a CT_CON, the special
         * case handling of con_attach() does not trigger. So all it would do
         * is calling TAILQ_INSERT_AFTER, but with the wrong container. So we
         * directly use the TAILQ macros. */
        current->parent = parent;
        TAILQ_INSERT_BEFORE(con, current, nodes);
        DLOG("attaching to focus list\n");
        TAILQ_INSERT_TAIL(&(parent->focus_head), current, focused);
        current->percent = con->percent;
    }
    DLOG("re-attached all\n");

    /* 3: restore focus, if con was focused */
    if (focus_next != NULL &&
        TAILQ_FIRST(&(parent->focus_head)) == con) {
        DLOG("restoring focus to focus_next=%p\n", focus_next);
        TAILQ_REMOVE(&(parent->focus_head), focus_next, focused);
        TAILQ_INSERT_HEAD(&(parent->focus_head), focus_next, focused);
        DLOG("restored focus.\n");
    }

    /* 4: close the redundant cons */
    DLOG("closing redundant cons\n");
    tree_close_internal(con, DONT_KILL_WINDOW, true);

    /* Well, we got to abort the recursion here because we destroyed the
     * container. However, if tree_flatten() is called sufficiently often,
     * there can’t be the situation of having two pairs of redundant containers
     * at once. Therefore, we can safely abort the recursion on this level
     * after flattening. */
    return;

recurse:
    /* We cannot use normal foreach here because tree_flatten might close the
     * current container. */
    current = TAILQ_FIRST(&(con->nodes_head));
    while (current != NULL) {
        Con *next = TAILQ_NEXT(current, nodes);
        tree_flatten(current);
        current = next;
    }

    current = TAILQ_FIRST(&(con->floating_head));
    while (current != NULL) {
        Con *next = TAILQ_NEXT(current, floating_windows);
        tree_flatten(current);
        current = next;
    }
}