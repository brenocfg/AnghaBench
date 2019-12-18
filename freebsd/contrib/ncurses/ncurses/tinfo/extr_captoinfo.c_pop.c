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
 int /*<<< orphan*/  _nc_warning (char*) ; 
 scalar_t__ onstack ; 
 int /*<<< orphan*/  param ; 
 scalar_t__* stack ; 
 size_t stackptr ; 

__attribute__((used)) static void
pop(void)
/* pop the top of the stack into onstack */
{
    if (stackptr == 0) {
	if (onstack == 0)
	    _nc_warning("I'm confused");
	else
	    onstack = 0;
    } else
	onstack = stack[--stackptr];
    param++;
}