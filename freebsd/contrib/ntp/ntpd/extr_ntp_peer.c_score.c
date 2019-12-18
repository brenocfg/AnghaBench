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
struct peer {int flash; scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ CTL_PST_SEL_EXCESS ; 
 scalar_t__ CTL_PST_SEL_SELCAND ; 
 int TEST10 ; 
 int TEST11 ; 
 int TEST12 ; 
 int TEST13 ; 

__attribute__((used)) static int
score(
	struct peer *peer	/* peer structure pointer */
	)
{
	int	temp;

	/*
	 * This routine calculates the premption score from the peer
	 * error bits and status. Increasing values are more cherished.
	 */
	temp = 0;
	if (!(peer->flash & TEST10))
		temp++;			/* 1 good synch and stratum */
	if (!(peer->flash & TEST13))
		temp++;			/* 2 reachable */
	if (!(peer->flash & TEST12))
		temp++;			/* 3 no loop */
	if (!(peer->flash & TEST11))
		temp++;			/* 4 good distance */
	if (peer->status >= CTL_PST_SEL_SELCAND)
		temp++;			/* 5 in the hunt */
	if (peer->status != CTL_PST_SEL_EXCESS)
		temp++;			/* 6 not spare tire */
	return (temp);			/* selection status */
}