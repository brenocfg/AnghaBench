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
struct target_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  solib_add (char*,int,struct target_ops*,int) ; 

__attribute__((used)) static void
sharedlibrary_command (char *args, int from_tty)
{
  dont_repeat ();
  solib_add (args, from_tty, (struct target_ops *) 0, 1);
}