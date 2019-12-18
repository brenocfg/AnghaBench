#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* close ) (TYPE_3__*) ;} ;
struct TYPE_9__ {TYPE_3__* log; } ;
struct TYPE_8__ {TYPE_2__* ep; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXF ;

/* Variables and functions */
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  log_init (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  tail (char*) ; 

__attribute__((used)) static void
log_err(
	SCR *sp,
	char *file,
	int line)
{
	EXF *ep;

	msgq(sp, M_SYSERR, "015|%s/%d: log put error", tail(file), line);
	ep = sp->ep;
	(void)ep->log->close(ep->log);
	if (!log_init(sp, ep))
		msgq(sp, M_ERR, "267|Log restarted");
}