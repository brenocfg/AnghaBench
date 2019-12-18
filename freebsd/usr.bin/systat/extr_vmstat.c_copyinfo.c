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
struct Info {long* intrcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (long*,long*,int) ; 
 int nintr ; 

__attribute__((used)) static void
copyinfo(struct Info *from, struct Info *to)
{
	long *intrcnt;

	/*
	 * time, wds, seek, and xfer are malloc'd so we have to
	 * save the pointers before the structure copy and then
	 * copy by hand.
	 */
	intrcnt = to->intrcnt;
	*to = *from;

	bcopy(from->intrcnt, to->intrcnt = intrcnt, nintr * sizeof (int));
}