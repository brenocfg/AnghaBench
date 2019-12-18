#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

const char *
command_ShowNegval(unsigned val)
{
  switch (val&3) {
    case 1: return "disabled & accepted";
    case 2: return "enabled & denied";
    case 3: return "enabled & accepted";
  }
  return "disabled & denied";
}