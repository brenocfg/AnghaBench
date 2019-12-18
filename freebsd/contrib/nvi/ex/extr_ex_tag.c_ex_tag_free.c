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
struct TYPE_3__ {int /*<<< orphan*/ * tag_last; int /*<<< orphan*/  tagfq; int /*<<< orphan*/  tq; } ;
typedef  int /*<<< orphan*/  TAGQ ;
typedef  int /*<<< orphan*/  TAGF ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EX_PRIVATE ;

/* Variables and functions */
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 void* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tagf_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tagq_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ex_tag_free(SCR *sp)
{
	EX_PRIVATE *exp;
	TAGF *tfp;
	TAGQ *tqp;

	/* Free up tag information. */
	exp = EXP(sp);
	while ((tqp = TAILQ_FIRST(exp->tq)) != NULL)
		tagq_free(sp, tqp);
	while ((tfp = TAILQ_FIRST(exp->tagfq)) != NULL)
		tagf_free(sp, tfp);
	if (exp->tag_last != NULL)
		free(exp->tag_last);
	return (0);
}