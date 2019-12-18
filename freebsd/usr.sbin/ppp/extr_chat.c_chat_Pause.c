#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct TYPE_3__ {char* name; struct chat* arg; int /*<<< orphan*/  func; int /*<<< orphan*/  load; } ;
struct chat {TYPE_1__ pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  chat_PauseTimer ; 
 int /*<<< orphan*/  timer_Start (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_1__*) ; 

__attribute__((used)) static void
chat_Pause(struct chat *c, u_long load)
{
  timer_Stop(&c->pause);
  c->pause.load += load;
  c->pause.func = chat_PauseTimer;
  c->pause.name = "chat pause";
  c->pause.arg = c;
  timer_Start(&c->pause);
}