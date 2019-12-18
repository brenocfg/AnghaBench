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
typedef  enum uni_callstate { ____Placeholder_uni_callstate } uni_callstate ;
typedef  enum call_state { ____Placeholder_call_state } call_state ;
struct TYPE_2__ {int ext; } ;

/* Variables and functions */
 TYPE_1__* callstates ; 

__attribute__((used)) static enum uni_callstate
map_callstate(enum call_state state)
{
	return (callstates[state].ext);
}