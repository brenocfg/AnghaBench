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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ GET_IB_USERLAND_TID (scalar_t__) ; 
 int getpid () ; 
 scalar_t__ random () ; 
 int /*<<< orphan*/  srandom (int) ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

uint64_t mad_trid(void)
{
	static uint64_t trid;
	uint64_t next;

	if (!trid) {
		srandom((int)time(0) * getpid());
		trid = random();
	}
	next = ++trid;
	next = GET_IB_USERLAND_TID(next);
	return next;
}