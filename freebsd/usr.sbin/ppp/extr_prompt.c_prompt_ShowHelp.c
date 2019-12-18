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
struct prompt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  prompt_Printf (struct prompt*,char*) ; 

__attribute__((used)) static void
prompt_ShowHelp(struct prompt *p)
{
  prompt_Printf(p, "The following commands are available:\n");
  prompt_Printf(p, " ~p\tEnter Packet mode\n");
  prompt_Printf(p, " ~t\tShow timers\n");
  prompt_Printf(p, " ~m\tShow memory map\n");
  prompt_Printf(p, " ~.\tTerminate program\n");
  prompt_Printf(p, " ~?\tThis help\n");
}