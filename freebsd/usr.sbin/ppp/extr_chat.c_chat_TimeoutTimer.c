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
struct chat {int TimedOut; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
chat_TimeoutTimer(void *v)
{
  struct chat *c = (struct chat *)v;
  timer_Stop(&c->timeout);
  c->TimedOut = 1;
}