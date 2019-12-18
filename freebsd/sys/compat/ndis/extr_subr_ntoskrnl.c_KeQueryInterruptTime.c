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
typedef  int uint64_t ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  getmicrouptime (struct timeval*) ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int tvtohz (struct timeval*) ; 

__attribute__((used)) static uint64_t
KeQueryInterruptTime(void)
{
	int ticks;
	struct timeval tv;

	getmicrouptime(&tv);

	ticks = tvtohz(&tv);

	return ticks * howmany(10000000, hz);
}