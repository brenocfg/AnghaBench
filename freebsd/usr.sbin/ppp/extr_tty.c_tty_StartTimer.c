#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; struct physical* arg; int /*<<< orphan*/  func; int /*<<< orphan*/  load; } ;
struct ttydevice {TYPE_2__ Timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct physical {TYPE_1__ link; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  SECTICKS ; 
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_Start (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_Timeout ; 

__attribute__((used)) static void
tty_StartTimer(struct physical *p)
{
  struct ttydevice *dev = device2tty(p->handler);

  timer_Stop(&dev->Timer);
  dev->Timer.load = SECTICKS;
  dev->Timer.func = tty_Timeout;
  dev->Timer.name = "tty CD";
  dev->Timer.arg = p;
  log_Printf(LogDEBUG, "%s: Using tty_Timeout [%p]\n",
             p->link.name, tty_Timeout);
  timer_Start(&dev->Timer);
}