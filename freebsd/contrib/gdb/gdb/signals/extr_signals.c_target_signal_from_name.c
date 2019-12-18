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
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int TARGET_SIGNAL_HUP ; 
 int TARGET_SIGNAL_LAST ; 
 int TARGET_SIGNAL_UNKNOWN ; 
 TYPE_1__* signals ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 

enum target_signal
target_signal_from_name (char *name)
{
  enum target_signal sig;

  /* It's possible we also should allow "SIGCLD" as well as "SIGCHLD"
     for TARGET_SIGNAL_SIGCHLD.  SIGIOT, on the other hand, is more
     questionable; seems like by now people should call it SIGABRT
     instead.  */

  /* This ugly cast brought to you by the native VAX compiler.  */
  for (sig = TARGET_SIGNAL_HUP;
       sig < TARGET_SIGNAL_LAST;
       sig = (enum target_signal) ((int) sig + 1))
    if (signals[sig].name != NULL
	&& strcmp (name, signals[sig].name) == 0)
      return sig;
  return TARGET_SIGNAL_UNKNOWN;
}