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

/* Variables and functions */
 int min (int,int) ; 

__attribute__((used)) static void
calculate_nqueues(int *t, int nc, const int c)
{
	int nq;

	if (*t > 0)
		return;
	nq = *t < 0 ? -*t : c;
	*t = min(nc, nq);
}