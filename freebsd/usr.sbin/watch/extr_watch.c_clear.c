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
 scalar_t__ clear_ok ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbuf ; 
 int /*<<< orphan*/  putchar ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clear(void)
{

	if (clear_ok)
		tputs(gbuf, 1, putchar);
	fflush(stdout);
}