#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * b_buf; int /*<<< orphan*/ * b_cg; } ;
struct bufarea {TYPE_1__ b_un; } ;
struct TYPE_4__ {scalar_t__ fs_ncg; } ;

/* Variables and functions */
 struct bufarea* cgbufs ; 
 int /*<<< orphan*/  flush (int /*<<< orphan*/ ,struct bufarea*) ; 
 scalar_t__ flushtries ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fswritefd ; 
 TYPE_2__ sblock ; 

int
flushentry(void)
{
	struct bufarea *cgbp;

	if (flushtries == sblock.fs_ncg || cgbufs == NULL)
		return (0);
	cgbp = &cgbufs[flushtries++];
	if (cgbp->b_un.b_cg == NULL)
		return (0);
	flush(fswritefd, cgbp);
	free(cgbp->b_un.b_buf);
	cgbp->b_un.b_buf = NULL;
	return (1);
}