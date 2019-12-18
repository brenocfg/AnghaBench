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
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int addstr4 (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ ) ; 

int
cl_addstr(SCR *sp, const char *str, size_t len)
{
	return addstr4(sp, (void *)str, len, 0);
}