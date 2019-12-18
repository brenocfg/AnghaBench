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
 int /*<<< orphan*/  flush_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  letter_delete_time (int,char*) ; 
 int /*<<< orphan*/  process_delayed_letters (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cron (void) {
  letter_delete_time (60, "Time expired");

  process_delayed_letters (0, 0);

  flush_all (0);
}