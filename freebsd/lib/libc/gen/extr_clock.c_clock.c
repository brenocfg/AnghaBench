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
struct rusage {int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; } ;
typedef  int /*<<< orphan*/  clock_t ;

/* Variables and functions */
 scalar_t__ CONVTCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUSAGE_SELF ; 
 scalar_t__ getrusage (int /*<<< orphan*/ ,struct rusage*) ; 

clock_t
clock(void)
{
	struct rusage ru;

	if (getrusage(RUSAGE_SELF, &ru))
		return ((clock_t) -1);
	return((clock_t)((CONVTCK(ru.ru_utime) + CONVTCK(ru.ru_stime))));
}