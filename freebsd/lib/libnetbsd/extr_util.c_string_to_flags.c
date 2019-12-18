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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int strtofflags (char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
string_to_flags(char **stringp, u_long *setp, u_long *clrp)
{

	return strtofflags(stringp, setp, clrp);
}