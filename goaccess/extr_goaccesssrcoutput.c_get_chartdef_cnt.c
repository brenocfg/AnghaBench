#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * def; } ;
typedef  int /*<<< orphan*/  GChartDef ;
typedef  TYPE_1__ GChart ;

/* Variables and functions */
 int /*<<< orphan*/  ChartDefStopper ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
get_chartdef_cnt (GChart * chart)
{
  GChartDef *def = chart->def;

  while (memcmp (def, &ChartDefStopper, sizeof ChartDefStopper))
    ++def;

  return def - chart->def;
}