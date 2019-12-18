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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRONG ; 
 int /*<<< orphan*/  time2 (struct tm*,int*,int) ; 

__attribute__((used)) static time_t
time1(
	struct tm * tmp
	)
{
	register time_t			t;
	int				okay;

	if (tmp->tm_isdst > 1)
		tmp->tm_isdst = 1;
	t = time2(tmp, &okay, 1);
	if (okay || tmp->tm_isdst < 0)
		return t;

	return WRONG;
}