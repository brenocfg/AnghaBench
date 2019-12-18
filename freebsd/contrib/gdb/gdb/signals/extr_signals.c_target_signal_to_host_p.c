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
 int /*<<< orphan*/  do_target_signal_to_host (int,int*) ; 

int
target_signal_to_host_p (enum target_signal oursig)
{
  int oursig_ok;
  do_target_signal_to_host (oursig, &oursig_ok);
  return oursig_ok;
}