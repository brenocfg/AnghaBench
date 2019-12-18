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
struct TYPE_4__ {int /*<<< orphan*/  (* req ) (struct authinfo*) ;} ;
struct authinfo {scalar_t__ retry; TYPE_1__* physical; int /*<<< orphan*/  authtimer; TYPE_2__ fn; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  datalink_AuthNotOk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct authinfo*) ; 
 int /*<<< orphan*/  timer_Start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
AuthTimeout(void *vauthp)
{
  struct authinfo *authp = (struct authinfo *)vauthp;

  timer_Stop(&authp->authtimer);
  if (--authp->retry > 0) {
    authp->id++;
    (*authp->fn.req)(authp);
    timer_Start(&authp->authtimer);
  } else {
    log_Printf(LogPHASE, "Auth: No response from server\n");
    datalink_AuthNotOk(authp->physical->dl);
  }
}