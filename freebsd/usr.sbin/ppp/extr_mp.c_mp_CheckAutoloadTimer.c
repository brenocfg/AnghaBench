#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ SamplePeriod; } ;
struct TYPE_10__ {TYPE_5__ total; } ;
struct TYPE_11__ {TYPE_2__ stats; } ;
struct TYPE_12__ {scalar_t__ period; } ;
struct TYPE_9__ {TYPE_4__ autoload; } ;
struct mp {TYPE_3__ link; int /*<<< orphan*/  bundle; TYPE_1__ cfg; } ;

/* Variables and functions */
 scalar_t__ bundle_WantAutoloadTimer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_StopAutoloadTimer (struct mp*) ; 
 int /*<<< orphan*/  mp_UpDown ; 
 int /*<<< orphan*/  throughput_callback (TYPE_5__*,int /*<<< orphan*/ ,struct mp*) ; 
 int /*<<< orphan*/  throughput_destroy (TYPE_5__*) ; 
 int /*<<< orphan*/  throughput_init (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  throughput_start (TYPE_5__*,char*,int) ; 

void
mp_CheckAutoloadTimer(struct mp *mp)
{
  if (mp->link.stats.total.SamplePeriod != mp->cfg.autoload.period) {
    throughput_destroy(&mp->link.stats.total);
    throughput_init(&mp->link.stats.total, mp->cfg.autoload.period);
    throughput_callback(&mp->link.stats.total, mp_UpDown, mp);
  }

  if (bundle_WantAutoloadTimer(mp->bundle))
    throughput_start(&mp->link.stats.total, "MP throughput", 1);
  else
    mp_StopAutoloadTimer(mp);
}