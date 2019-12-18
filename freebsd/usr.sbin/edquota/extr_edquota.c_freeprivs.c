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
struct quotause {struct quotause* next; int /*<<< orphan*/  qf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct quotause*) ; 
 int /*<<< orphan*/  quota_close (int /*<<< orphan*/ ) ; 

void
freeprivs(struct quotause *quplist)
{
	struct quotause *qup, *nextqup;

	for (qup = quplist; qup; qup = nextqup) {
		quota_close(qup->qf);
		nextqup = qup->next;
		free(qup);
	}
}