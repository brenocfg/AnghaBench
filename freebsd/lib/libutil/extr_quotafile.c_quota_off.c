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
struct quotafile {int /*<<< orphan*/  quotatype; int /*<<< orphan*/  fsname; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_QUOTAOFF ; 
 int quotactl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
quota_off(struct quotafile *qf)
{

	return (quotactl(qf->fsname, QCMD(Q_QUOTAOFF, qf->quotatype), 0, 0));
}