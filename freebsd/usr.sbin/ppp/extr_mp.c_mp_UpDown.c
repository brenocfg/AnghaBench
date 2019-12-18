#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int max; int min; } ;
struct TYPE_15__ {TYPE_6__ autoload; } ;
struct TYPE_10__ {int /*<<< orphan*/  OctetsPerSecond; } ;
struct TYPE_9__ {int /*<<< orphan*/  OctetsPerSecond; } ;
struct TYPE_11__ {TYPE_2__ out; TYPE_1__ in; } ;
struct TYPE_12__ {TYPE_3__ total; } ;
struct TYPE_13__ {TYPE_4__ stats; } ;
struct mp {TYPE_8__* bundle; TYPE_7__ cfg; TYPE_5__ link; } ;
struct TYPE_16__ {int bandwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_DOWN ; 
 int /*<<< orphan*/  AUTO_UP ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_AutoAdjust (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
mp_UpDown(void *v)
{
  struct mp *mp = (struct mp *)v;
  int percent;

  percent = MAX(mp->link.stats.total.in.OctetsPerSecond,
                mp->link.stats.total.out.OctetsPerSecond) * 800 /
            mp->bundle->bandwidth;
  if (percent >= mp->cfg.autoload.max) {
    log_Printf(LogDEBUG, "%d%% saturation - bring a link up ?\n", percent);
    bundle_AutoAdjust(mp->bundle, percent, AUTO_UP);
  } else if (percent <= mp->cfg.autoload.min) {
    log_Printf(LogDEBUG, "%d%% saturation - bring a link down ?\n", percent);
    bundle_AutoAdjust(mp->bundle, percent, AUTO_DOWN);
  }
}