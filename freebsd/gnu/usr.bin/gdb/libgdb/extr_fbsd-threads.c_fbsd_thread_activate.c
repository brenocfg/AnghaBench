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

/* Variables and functions */
 int /*<<< orphan*/  enable_thread_event_reporting () ; 
 int fbsd_thread_active ; 
 scalar_t__ fbsd_thread_core ; 
 int /*<<< orphan*/  fbsd_thread_find_new_threads () ; 
 int /*<<< orphan*/  get_current_thread () ; 
 int /*<<< orphan*/  init_thread_list () ; 

__attribute__((used)) static void
fbsd_thread_activate (void)
{
  fbsd_thread_active = 1;
  init_thread_list();
  if (fbsd_thread_core == 0)
    enable_thread_event_reporting ();
  fbsd_thread_find_new_threads ();
  get_current_thread ();
}