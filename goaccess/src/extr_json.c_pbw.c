#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bandwidth; scalar_t__ json_pretty_print; } ;
struct TYPE_5__ {int /*<<< orphan*/  nbw; } ;
struct TYPE_6__ {int /*<<< orphan*/  bw_perc; TYPE_1__ bw; } ;
typedef  TYPE_2__ GMetrics ;
typedef  int /*<<< orphan*/  GJSON ;

/* Variables and functions */
 TYPE_4__ conf ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  popen_obj_attr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pskeyfval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pskeyu64val (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pbw (GJSON * json, GMetrics * nmetrics, int sp)
{
  int isp = 0;

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1;

  if (!conf.bandwidth)
    return;

  popen_obj_attr (json, "bytes", sp);
  /* print bandwidth */
  pskeyu64val (json, "count", nmetrics->bw.nbw, isp, 0);
  /* print bandwidth percent */
  pskeyfval (json, "percent", nmetrics->bw_perc, isp, 1);
  pclose_obj (json, sp, 0);
}