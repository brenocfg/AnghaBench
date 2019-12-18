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
struct TYPE_3__ {int ei; int /*<<< orphan*/ * msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int nitems (TYPE_1__*) ; 
 TYPE_1__* trap_data ; 

__attribute__((used)) static bool
trap_enable_intr(int trapno)
{

	MPASS(trapno > 0);
	if (trapno < nitems(trap_data) && trap_data[trapno].msg != NULL)
		return (trap_data[trapno].ei);
	return (false);
}