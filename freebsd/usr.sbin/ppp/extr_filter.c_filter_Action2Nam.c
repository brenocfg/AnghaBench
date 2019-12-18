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
typedef  int /*<<< orphan*/  actname ;

/* Variables and functions */
 unsigned int A_NONE ; 
 unsigned int MAXFILTERS ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

const char *
filter_Action2Nam(unsigned act)
{
  static const char * const actname[] = { "  none ", "permit ", "  deny " };
  static char buf[8];

  if (act < MAXFILTERS) {
    snprintf(buf, sizeof buf, "%6d ", act);
    return buf;
  } else if (act >= A_NONE && act < A_NONE + sizeof(actname)/sizeof(char *))
    return actname[act - A_NONE];
  else
    return "?????? ";
}