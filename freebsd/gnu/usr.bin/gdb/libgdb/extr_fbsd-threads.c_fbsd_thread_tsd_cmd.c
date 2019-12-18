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
 scalar_t__ fbsd_thread_active ; 
 int /*<<< orphan*/  td_ta_tsd_iter_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_agent ; 
 int /*<<< orphan*/  tsd_cb ; 

__attribute__((used)) static void
fbsd_thread_tsd_cmd (char *exp, int from_tty)
{
  if (fbsd_thread_active)
    td_ta_tsd_iter_p (thread_agent, tsd_cb, NULL);
}