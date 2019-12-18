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
struct fsm {TYPE_7__* link; TYPE_4__* bundle; } ;
struct TYPE_13__ {int required; } ;
struct TYPE_14__ {TYPE_5__ mppe; } ;
struct TYPE_16__ {TYPE_6__ cfg; } ;
struct TYPE_15__ {TYPE_8__ ccp; } ;
struct TYPE_10__ {scalar_t__ policy; } ;
struct TYPE_9__ {scalar_t__* file; } ;
struct TYPE_11__ {TYPE_2__ mppe; TYPE_1__ cfg; } ;
struct TYPE_12__ {TYPE_3__ radius; } ;

/* Variables and functions */
 scalar_t__ MPPE_POLICY_REQUIRED ; 

__attribute__((used)) static int
MPPERequired(struct fsm *fp)
{
#ifndef NORADIUS
  /*
   * If the radius server gave us RAD_MICROSOFT_MS_MPPE_ENCRYPTION_POLICY,
   * use that instead of our configuration value.
   */
  if (*fp->bundle->radius.cfg.file && fp->bundle->radius.mppe.policy)
    return fp->bundle->radius.mppe.policy == MPPE_POLICY_REQUIRED ? 1 : 0;
#endif

  return fp->link->ccp.cfg.mppe.required;
}