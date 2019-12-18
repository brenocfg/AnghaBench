#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_4__ {scalar_t__ lt_dow; } ;
typedef  TYPE_1__ login_time_t ;

/* Variables and functions */
 int LC_MAXTIMES ; 
 scalar_t__ LTM_NONE ; 
 scalar_t__ in_ltm (TYPE_1__ const*,struct tm*,int /*<<< orphan*/ *) ; 

int
in_ltms(const login_time_t *ltm, struct tm *tm, time_t *t)
{
    int	    i = 0;

    while (i < LC_MAXTIMES && ltm[i].lt_dow != LTM_NONE) {
	if (in_ltm(ltm + i, tm, t))
	    return (i);
	i++;
    }
    return (-1);
}