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
struct TYPE_6__ {int incs; } ;
struct TYPE_4__ {int timeout; int inc; int maxinc; } ;
struct TYPE_5__ {TYPE_1__ dial; } ;
struct datalink {TYPE_3__ dial; TYPE_2__ cfg; } ;

/* Variables and functions */

int
datalink_GetDialTimeout(struct datalink *dl)
{
  int result = dl->cfg.dial.timeout + dl->dial.incs * dl->cfg.dial.inc;

  if (dl->dial.incs < dl->cfg.dial.maxinc)
    dl->dial.incs++;

  return result;
}