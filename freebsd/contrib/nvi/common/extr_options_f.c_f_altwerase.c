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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  O_CLR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_TTYWERASE ; 

int
f_altwerase(
	SCR *sp,
	OPTION *op,
	char *str,
	u_long *valp)
{
	if (*valp)
		O_CLR(sp, O_TTYWERASE);
	return (0);
}