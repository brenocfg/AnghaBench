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
struct TYPE_2__ {int /*<<< orphan*/  events_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ScriptStart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Script_StackPush_b () ; 
 TYPE_1__* actors ; 
 size_t script_actor ; 

void Script_ActorInvoke_b()
{
  Script_StackPush_b();
  ScriptStart(&actors[script_actor].events_ptr);
}