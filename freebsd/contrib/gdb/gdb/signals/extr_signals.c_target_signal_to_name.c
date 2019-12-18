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
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int TARGET_SIGNAL_FIRST ; 
 int TARGET_SIGNAL_LAST ; 
 TYPE_1__* signals ; 

char *
target_signal_to_name (enum target_signal sig)
{
  if ((sig >= TARGET_SIGNAL_FIRST) && (sig <= TARGET_SIGNAL_LAST)
      && signals[sig].name != NULL)
    return signals[sig].name;
  else
    /* I think the code which prints this will always print it along
       with the string, so no need to be verbose (very old comment).  */
    return "?";
}