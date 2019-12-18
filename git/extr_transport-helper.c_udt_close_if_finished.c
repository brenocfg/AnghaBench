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
struct unidirectional_transfer {int /*<<< orphan*/  dest_name; int /*<<< orphan*/  dest; scalar_t__ dest_is_sock; int /*<<< orphan*/  state; int /*<<< orphan*/  bufuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  SSTATE_FINISHED ; 
 scalar_t__ STATE_NEEDS_CLOSING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transfer_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udt_close_if_finished(struct unidirectional_transfer *t)
{
	if (STATE_NEEDS_CLOSING(t->state) && !t->bufuse) {
		t->state = SSTATE_FINISHED;
		if (t->dest_is_sock)
			shutdown(t->dest, SHUT_WR);
		else
			close(t->dest);
		transfer_debug("Closed %s.", t->dest_name);
	}
}