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
struct event_timer {scalar_t__ h_idx; int /*<<< orphan*/  wakeup; scalar_t__ wakeup_time; } ;
struct udp_target {struct event_timer confirm_timer; } ;

/* Variables and functions */
 scalar_t__ CONFIRM_TIMEOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  confirm_gateway ; 
 int /*<<< orphan*/  insert_event_timer (struct event_timer*) ; 
 scalar_t__ precise_now ; 

void start_confirm_timer (struct udp_target *S) {
  struct event_timer *ev = &S->confirm_timer;
  ev->wakeup_time = precise_now + CONFIRM_TIMEOUT;
  ev->wakeup = confirm_gateway;
  assert (!ev->h_idx);
  ev->h_idx = 0;
  insert_event_timer (ev);
}