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
struct TYPE_2__ {scalar_t__ load; } ;
struct chat {TYPE_1__ pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  timer_Stop (TYPE_1__*) ; 

__attribute__((used)) static void
chat_PauseTimer(void *v)
{
  struct chat *c = (struct chat *)v;
  timer_Stop(&c->pause);
  c->pause.load = 0;
}