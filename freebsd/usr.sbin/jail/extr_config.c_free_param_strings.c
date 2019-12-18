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
struct cfvar {int /*<<< orphan*/  vars; struct cfvar* name; struct cfvar* s; } ;
struct cfstring {int /*<<< orphan*/  vars; struct cfstring* name; struct cfstring* s; } ;
struct cfparam {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 struct cfvar* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cfvar* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cfvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cfvar*) ; 
 int /*<<< orphan*/  tq ; 

__attribute__((used)) static void
free_param_strings(struct cfparam *p)
{
	struct cfstring *s;
	struct cfvar *v;

	while ((s = TAILQ_FIRST(&p->val))) {
		free(s->s);
		while ((v = STAILQ_FIRST(&s->vars))) {
			free(v->name);
			STAILQ_REMOVE_HEAD(&s->vars, tq);
			free(v);
		}
		TAILQ_REMOVE(&p->val, s, tq);
		free(s);
	}
}