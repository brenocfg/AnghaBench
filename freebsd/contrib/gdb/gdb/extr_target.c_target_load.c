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
struct TYPE_2__ {int /*<<< orphan*/  (* to_load ) (char*,int) ;} ;

/* Variables and functions */
 TYPE_1__ current_target ; 
 int /*<<< orphan*/  dcache_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int /*<<< orphan*/  target_dcache ; 

void
target_load (char *arg, int from_tty)
{
  dcache_invalidate (target_dcache);
  (*current_target.to_load) (arg, from_tty);
}