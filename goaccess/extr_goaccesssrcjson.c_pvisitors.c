#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ json_pretty_print; } ;
struct TYPE_4__ {int /*<<< orphan*/  visitors_perc; int /*<<< orphan*/  visitors; } ;
typedef  TYPE_1__ GMetrics ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 TYPE_3__ conf ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  popen_obj_attr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pskeyfval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pskeyival (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pvisitors (GJSON * json, GMetrics * nmetrics, int sp)
{
  int isp = 0;

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1;

  popen_obj_attr (json, "visitors", sp);
  /* print visitors */
  pskeyival (json, "count", nmetrics->visitors, isp, 0);
  /* print visitors percent */
  pskeyfval (json, "percent", nmetrics->visitors_perc, isp, 1);
  pclose_obj (json, sp, 0);
}