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
struct clocktime {int year; int mon; int day; int hour; int min; int sec; int nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int* nsdivisors ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,...) ; 

void
clock_print_ct(const struct clocktime *ct, int nsdigits)
{

	KASSERT(nsdigits >= 0 && nsdigits <= 9, ("bad nsdigits %d", nsdigits));

	if (nsdigits > 0) {
		printf("%04d-%02d-%02d %02d:%02d:%02d.%*.*ld",
		    ct->year, ct->mon, ct->day,
		    ct->hour, ct->min, ct->sec,
		    nsdigits, nsdigits, ct->nsec / nsdivisors[nsdigits]);
	} else {
		printf("%04d-%02d-%02d %02d:%02d:%02d",
		    ct->year, ct->mon, ct->day,
		    ct->hour, ct->min, ct->sec);
	}
}