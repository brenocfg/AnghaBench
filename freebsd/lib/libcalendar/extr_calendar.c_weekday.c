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
struct TYPE_3__ {int member_0; int member_1; int member_2; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */
 int ndaysgi (TYPE_1__*) ; 

int
weekday(int nd)
{
	date dmondaygi = {1997, 8, 16}; /* Internal repr. of 1997-11-17 */
	static int nmonday;             /* ... which is a monday        */ 

	/* Cache the daynumber of one monday */
	if (nmonday == 0)
		nmonday = ndaysgi(&dmondaygi);

	/* return (nd - nmonday) modulo 7 which is the weekday */
	nd = (nd - nmonday) % 7;
	if (nd < 0)
		return (nd + 7);
	else
		return (nd);
}