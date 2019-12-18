#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {int argc; int argn; int /*<<< orphan*/ * argv; TYPE_3__* cx; } ;
struct TYPE_4__ {void* max; void* timeout; } ;
struct TYPE_5__ {TYPE_1__ reconnect; } ;
struct TYPE_6__ {TYPE_2__ cfg; } ;

/* Variables and functions */
 void* atoi (int /*<<< orphan*/ ) ; 

int
datalink_SetReconnect(struct cmdargs const *arg)
{
  if (arg->argc == arg->argn+2) {
    arg->cx->cfg.reconnect.timeout = atoi(arg->argv[arg->argn]);
    arg->cx->cfg.reconnect.max = atoi(arg->argv[arg->argn+1]);
    return 0;
  }
  return -1;
}