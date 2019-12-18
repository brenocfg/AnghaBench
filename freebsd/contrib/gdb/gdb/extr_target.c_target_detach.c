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
struct TYPE_2__ {int /*<<< orphan*/  (* to_detach ) (char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DO_DEFERRED_STORES ; 
 TYPE_1__ current_target ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 

void
target_detach (char *args, int from_tty)
{
  /* Handle any optimized stores to the inferior.  */
#ifdef DO_DEFERRED_STORES
  DO_DEFERRED_STORES;
#endif
  (current_target.to_detach) (args, from_tty);
}