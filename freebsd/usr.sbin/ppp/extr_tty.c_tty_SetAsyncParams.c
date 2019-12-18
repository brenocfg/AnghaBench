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
typedef  int u_int32_t ;
struct ttydevice {char* hook; int /*<<< orphan*/  cs; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct physical {int /*<<< orphan*/  async; TYPE_1__ link; int /*<<< orphan*/  handler; } ;
struct ng_async_cfg {int enabled; int accm; int /*<<< orphan*/  smru; int /*<<< orphan*/  amru; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  MAX_MRU ; 
 int /*<<< orphan*/  MAX_MTU ; 
 int /*<<< orphan*/  NGM_ASYNC_CMD_SET_CONFIG ; 
 int /*<<< orphan*/  NGM_ASYNC_COOKIE ; 
 int NG_PATHSIZ ; 
 scalar_t__ NgSendMsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ng_async_cfg*,int) ; 
 int /*<<< orphan*/  async_SetLinkParams (int /*<<< orphan*/ *,int,int) ; 
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 scalar_t__ isngtty (struct ttydevice*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  memset (struct ng_async_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
tty_SetAsyncParams(struct physical *p, u_int32_t mymap, u_int32_t hismap)
{
  struct ttydevice *dev = device2tty(p->handler);
  char asyncpath[NG_PATHSIZ];
  struct ng_async_cfg cfg;

  if (isngtty(dev)) {
    /* Configure the async converter node */

    snprintf(asyncpath, sizeof asyncpath, ".:%s", dev->hook);
    memset(&cfg, 0, sizeof cfg);
    cfg.enabled = 1;
    cfg.accm = mymap | hismap;
    cfg.amru = MAX_MTU;
    cfg.smru = MAX_MRU;
    log_Printf(LogDEBUG, "Configure async node at %s\n", asyncpath);
    if (NgSendMsg(dev->cs, asyncpath, NGM_ASYNC_COOKIE,
                  NGM_ASYNC_CMD_SET_CONFIG, &cfg, sizeof cfg) < 0)
      log_Printf(LogWARN, "%s: Can't configure async node at %s\n",
                 p->link.name, asyncpath);
  } else
    /* No netgraph node, just config the async layer */
    async_SetLinkParams(&p->async, mymap, hismap);
}