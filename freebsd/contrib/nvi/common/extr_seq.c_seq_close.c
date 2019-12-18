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
struct TYPE_3__ {int /*<<< orphan*/  seqq; } ;
typedef  int /*<<< orphan*/  SEQ ;
typedef  TYPE_1__ GS ;

/* Variables and functions */
 int /*<<< orphan*/ * SLIST_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  seq_free (int /*<<< orphan*/ *) ; 

void
seq_close(GS *gp)
{
	SEQ *qp;

	while ((qp = SLIST_FIRST(gp->seqq)) != NULL) {
		SLIST_REMOVE_HEAD(gp->seqq, q);
		(void)seq_free(qp);
	}
}