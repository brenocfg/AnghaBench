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
struct ccdata {scalar_t__ cookie; struct cc_funcs const* funcs; int /*<<< orphan*/  free_sigs; int /*<<< orphan*/  def_sigs; int /*<<< orphan*/  sigs; int /*<<< orphan*/  orphaned_conns; int /*<<< orphan*/  port_list; int /*<<< orphan*/  user_list; } ;
struct cc_funcs {int dummy; } ;

/* Variables and functions */
 struct ccdata* CCMALLOC (int) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 

struct ccdata *
cc_create(const struct cc_funcs *vtab)
{
	struct ccdata *cc;

	cc = CCMALLOC(sizeof(*cc));
	if (cc == NULL)
		return (NULL);

	LIST_INIT(&cc->user_list);
	TAILQ_INIT(&cc->port_list);
	LIST_INIT(&cc->orphaned_conns);
	TAILQ_INIT(&cc->sigs);
	TAILQ_INIT(&cc->def_sigs);
	TAILQ_INIT(&cc->free_sigs);
	cc->funcs = vtab;
	cc->cookie = 0;

	return (cc);
}