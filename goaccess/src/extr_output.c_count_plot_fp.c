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
struct TYPE_5__ {TYPE_1__* chart; } ;
struct TYPE_4__ {scalar_t__ plot; } ;
typedef  TYPE_2__ GHTML ;

/* Variables and functions */

__attribute__((used)) static int
count_plot_fp (const GHTML * def)
{
  int i = 0;
  for (i = 0; def->chart[i].plot != 0; ++i);
  return i;
}