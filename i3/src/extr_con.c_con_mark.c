#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* name; } ;
typedef  TYPE_1__ mark_t ;
typedef  scalar_t__ mark_mode_t ;
struct TYPE_10__ {int mark_changed; int /*<<< orphan*/  marks_head; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 scalar_t__ MM_REPLACE ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_unmark (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  ipc_send_window_event (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  marks ; 
 TYPE_1__* scalloc (int,int) ; 
 char const* sstrdup (char const*) ; 

void con_mark(Con *con, const char *mark, mark_mode_t mode) {
    assert(con != NULL);
    DLOG("Setting mark \"%s\" on con = %p.\n", mark, con);

    con_unmark(NULL, mark);
    if (mode == MM_REPLACE) {
        DLOG("Removing all existing marks on con = %p.\n", con);

        mark_t *current;
        while (!TAILQ_EMPTY(&(con->marks_head))) {
            current = TAILQ_FIRST(&(con->marks_head));
            con_unmark(con, current->name);
        }
    }

    mark_t *new = scalloc(1, sizeof(mark_t));
    new->name = sstrdup(mark);
    TAILQ_INSERT_TAIL(&(con->marks_head), new, marks);
    ipc_send_window_event("mark", con);

    con->mark_changed = true;
}