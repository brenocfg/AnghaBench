#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* def; } ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ GChartDef ;
typedef  TYPE_2__ GChart ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fpskeyaval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fpskeysval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
print_d3_chart_def_axis (FILE * fp, GChart * chart, size_t cnt, int isp)
{
  GChartDef *def = chart->def;
  size_t j = 0;

  for (j = 0; j < cnt; ++j) {
    if (strchr (def[j].value, '[') != NULL)
      fpskeyaval (fp, def[j].key, def[j].value, isp, j == cnt - 1);
    else
      fpskeysval (fp, def[j].key, def[j].value, isp, j == cnt - 1);
  }
}