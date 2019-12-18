#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct TYPE_2__ {int /*<<< orphan*/  func_code; } ;
struct ccb_relsim {scalar_t__ qfrozen_cnt; scalar_t__ release_timeout; scalar_t__ openings; int /*<<< orphan*/  release_flags; TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  crs ;

/* Variables and functions */
 int /*<<< orphan*/  RELSIM_RELEASE_AFTER_QEMPTY ; 
 int /*<<< orphan*/  XPT_REL_SIMQ ; 
 int /*<<< orphan*/  bzero (struct ccb_relsim*,int) ; 
 int /*<<< orphan*/  send_ccb (union ccb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rel_simq()
{
	struct ccb_relsim crs;

	bzero(&crs, sizeof(crs));
	crs.ccb_h.func_code = XPT_REL_SIMQ;
	crs.release_flags = RELSIM_RELEASE_AFTER_QEMPTY;
	crs.openings = 0;
	crs.release_timeout = 0;
	crs.qfrozen_cnt = 0;
	send_ccb((union ccb *)&crs, /*priority*/0);
}