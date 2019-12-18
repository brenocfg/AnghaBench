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
struct datalink {int state; } ;

/* Variables and functions */
 char const** states ; 

const char *
datalink_State(struct datalink *dl)
{
  if (dl->state >= sizeof states / sizeof states[0])
    return "unknown";
  return states[dl->state];
}