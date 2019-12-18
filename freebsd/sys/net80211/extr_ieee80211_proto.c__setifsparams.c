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
struct wmeParams {int /*<<< orphan*/  wmep_txopLimit; int /*<<< orphan*/  wmep_logcwmax; int /*<<< orphan*/  wmep_logcwmin; int /*<<< orphan*/  wmep_aifsn; } ;
struct TYPE_3__ {int /*<<< orphan*/  txopLimit; int /*<<< orphan*/  logcwmax; int /*<<< orphan*/  logcwmin; int /*<<< orphan*/  aifsn; } ;
typedef  TYPE_1__ paramType ;

/* Variables and functions */

__attribute__((used)) static void
_setifsparams(struct wmeParams *wmep, const paramType *phy)
{
	wmep->wmep_aifsn = phy->aifsn;
	wmep->wmep_logcwmin = phy->logcwmin;	
	wmep->wmep_logcwmax = phy->logcwmax;		
	wmep->wmep_txopLimit = phy->txopLimit;
}