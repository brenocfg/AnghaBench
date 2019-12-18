#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mark_mode_t ;
typedef  int /*<<< orphan*/  Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ con_has_mark (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  con_mark (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_unmark (int /*<<< orphan*/ *,char const*) ; 

void con_mark_toggle(Con *con, const char *mark, mark_mode_t mode) {
    assert(con != NULL);
    DLOG("Toggling mark \"%s\" on con = %p.\n", mark, con);

    if (con_has_mark(con, mark)) {
        con_unmark(con, mark);
    } else {
        con_mark(con, mark, mode);
    }
}