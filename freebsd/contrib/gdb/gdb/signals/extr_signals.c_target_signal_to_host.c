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
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;

/* Variables and functions */
 int do_target_signal_to_host (int,int*) ; 
 int /*<<< orphan*/  target_signal_to_name (int) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

int
target_signal_to_host (enum target_signal oursig)
{
  int oursig_ok;
  int targ_signo = do_target_signal_to_host (oursig, &oursig_ok);
  if (!oursig_ok)
    {
      /* The user might be trying to do "signal SIGSAK" where this system
         doesn't have SIGSAK.  */
      warning ("Signal %s does not exist on this system.\n",
	       target_signal_to_name (oursig));
      return 0;
    }
  else
    return targ_signo;
}