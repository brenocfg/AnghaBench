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
struct cmdargs {int argc; int argn; int /*<<< orphan*/  bundle; TYPE_1__* cx; int /*<<< orphan*/ * argv; } ;
struct TYPE_4__ {int bandwidth; } ;
struct TYPE_3__ {scalar_t__ state; TYPE_2__ mp; } ;

/* Variables and functions */
 scalar_t__ DATALINK_OPEN ; 
 int /*<<< orphan*/  LogWARN ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_CalculateBandwidth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 

int
mp_SetDatalinkBandwidth(struct cmdargs const *arg)
{
  int val;

  if (arg->argc != arg->argn+1)
    return -1;

  val = atoi(arg->argv[arg->argn]);
  if (val <= 0) {
    log_Printf(LogWARN, "The link bandwidth must be greater than zero\n");
    return 1;
  }
  arg->cx->mp.bandwidth = val;

  if (arg->cx->state == DATALINK_OPEN)
    bundle_CalculateBandwidth(arg->bundle);

  return 0;
}