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
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_my_cleanups (int /*<<< orphan*/ *,struct cleanup*) ; 
 int /*<<< orphan*/  exec_error_cleanup_chain ; 

void
do_exec_error_cleanups (struct cleanup *old_chain)
{
  do_my_cleanups (&exec_error_cleanup_chain, old_chain);
}