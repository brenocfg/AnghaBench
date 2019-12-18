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
struct quotause {int /*<<< orphan*/  fsname; int /*<<< orphan*/  dqblk; int /*<<< orphan*/  qf; struct quotause* next; } ;

/* Variables and functions */
 int quota_write_limits (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

void
putprivs(long id, struct quotause *quplist)
{
	struct quotause *qup;

	for (qup = quplist; qup; qup = qup->next)
		if (quota_write_limits(qup->qf, &qup->dqblk, id) == -1)
			warn("%s", qup->fsname);
}