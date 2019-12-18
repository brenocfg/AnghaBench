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
struct bcd_clocktime {int year; int mon; int day; int hour; int min; int sec; int nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int* nsdivisors ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,...) ; 

void
clock_print_bcd(const struct bcd_clocktime *bct, int nsdigits)
{

	KASSERT(nsdigits >= 0 && nsdigits <= 9, ("bad nsdigits %d", nsdigits));

	if (nsdigits > 0) {
		printf("%4.4x-%2.2x-%2.2x %2.2x:%2.2x:%2.2x.%*.*ld",
		    bct->year, bct->mon, bct->day,
		    bct->hour, bct->min, bct->sec,
		    nsdigits, nsdigits, bct->nsec / nsdivisors[nsdigits]);
	} else {
		printf("%4.4x-%2.2x-%2.2x %2.2x:%2.2x:%2.2x",
		    bct->year, bct->mon, bct->day,
		    bct->hour, bct->min, bct->sec);
	}
}