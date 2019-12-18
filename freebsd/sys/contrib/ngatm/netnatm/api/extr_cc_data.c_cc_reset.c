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
struct ccdata {scalar_t__ cookie; int /*<<< orphan*/  orphaned_conns; int /*<<< orphan*/  user_list; int /*<<< orphan*/  port_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cc_conn_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_port_destroy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cc_sig_flush_all (struct ccdata*) ; 
 int /*<<< orphan*/  cc_user_destroy (int /*<<< orphan*/ ) ; 

void
cc_reset(struct ccdata *cc)
{

	while (!LIST_EMPTY(&cc->user_list))
		cc_user_destroy(LIST_FIRST(&cc->user_list));

	while (!TAILQ_EMPTY(&cc->port_list))
		cc_port_destroy(TAILQ_FIRST(&cc->port_list), 1);

	while (!LIST_EMPTY(&cc->orphaned_conns))
		cc_conn_destroy(LIST_FIRST(&cc->orphaned_conns));

	CCASSERT(LIST_EMPTY(&cc->user_list),
	    ("user list not empty"));
	CCASSERT(LIST_EMPTY(&cc->orphaned_conns),
	    ("still orphaned conns"));

	cc_sig_flush_all(cc);

	cc->cookie = 0;
}