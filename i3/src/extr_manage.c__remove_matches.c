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
struct TYPE_3__ {int /*<<< orphan*/  swallow_head; } ;
typedef  int /*<<< orphan*/  Match ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matches ; 

__attribute__((used)) static void _remove_matches(Con *con) {
    while (!TAILQ_EMPTY(&(con->swallow_head))) {
        Match *first = TAILQ_FIRST(&(con->swallow_head));
        TAILQ_REMOVE(&(con->swallow_head), first, matches);
        match_free(first);
        free(first);
    }
}