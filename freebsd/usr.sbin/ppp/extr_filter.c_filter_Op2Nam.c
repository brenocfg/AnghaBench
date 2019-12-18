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
 char const** opname ; 

const char *
filter_Op2Nam(unsigned op)
{
  if (op >= sizeof opname / sizeof opname[0])
    return "unknown";
  return opname[op];

}