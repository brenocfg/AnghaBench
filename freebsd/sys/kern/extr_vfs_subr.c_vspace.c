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
 scalar_t__ desiredvnodes ; 
 scalar_t__ freevnodes ; 
 int gapvnodes ; 
 int imax (scalar_t__,int) ; 
 scalar_t__ numvnodes ; 
 int vhiwat ; 
 int vlowat ; 
 scalar_t__ wantfreevnodes ; 

__attribute__((used)) static int
vspace(void)
{
	int space;

	gapvnodes = imax(desiredvnodes - wantfreevnodes, 100);
	vhiwat = gapvnodes / 11; /* 9% -- just under the 10% in vlrureclaim() */
	vlowat = vhiwat / 2;
	if (numvnodes > desiredvnodes)
		return (0);
	space = desiredvnodes - numvnodes;
	if (freevnodes > wantfreevnodes)
		space += freevnodes - wantfreevnodes;
	return (space);
}