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
struct cfjail {int /*<<< orphan*/ * queue; int /*<<< orphan*/ * dep; int /*<<< orphan*/  params; } ;

/* Variables and functions */
 size_t DEP_FROM ; 
 size_t DEP_TO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cfjail*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfjails ; 
 struct cfjail* emalloc (int) ; 
 int /*<<< orphan*/  memset (struct cfjail*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tq ; 

struct cfjail *
add_jail(void)
{
	struct cfjail *j;

	j = emalloc(sizeof(struct cfjail));
	memset(j, 0, sizeof(struct cfjail));
	TAILQ_INIT(&j->params);
	STAILQ_INIT(&j->dep[DEP_FROM]);
	STAILQ_INIT(&j->dep[DEP_TO]);
	j->queue = &cfjails;
	TAILQ_INSERT_TAIL(&cfjails, j, tq);
	return j;
}