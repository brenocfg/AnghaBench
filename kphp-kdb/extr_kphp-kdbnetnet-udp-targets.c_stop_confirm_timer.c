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
struct udp_target {int /*<<< orphan*/  confirm_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_event_timer (int /*<<< orphan*/ *) ; 

void stop_confirm_timer (struct udp_target *S) {
  remove_event_timer (&S->confirm_timer);
}