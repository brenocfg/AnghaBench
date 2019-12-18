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
struct objfile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_uw_thread () ; 
 int /*<<< orphan*/  libthread_init () ; 
 int /*<<< orphan*/  target_new_objfile_chain (struct objfile*) ; 
 scalar_t__ uw_thread_active ; 

__attribute__((used)) static void
uw_thread_new_objfile (struct objfile *objfile)
{
  if (objfile)
    libthread_init ();

  else if (uw_thread_active)
    deactivate_uw_thread ();

  if (target_new_objfile_chain)
    target_new_objfile_chain (objfile);
}