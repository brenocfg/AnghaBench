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
struct TYPE_2__ {int mode; char const* name; } ;

/* Variables and functions */
 TYPE_1__* modes ; 

const char *
mode2Nam(int mode)
{
  int m;

  for (m = 0; modes[m].mode; m++)
    if (modes[m].mode == mode)
      return modes[m].name;

  return "unknown";
}