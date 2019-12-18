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
typedef  int /*<<< orphan*/  updn_switch_dir_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOWN ; 
 int /*<<< orphan*/  UP ; 

__attribute__((used)) static updn_switch_dir_t updn_get_dir(unsigned cur_rank, unsigned rem_rank,
				      uint64_t cur_id, uint64_t rem_id)
{
	/* HACK: comes to solve root nodes connection, in a classic subnet root nodes do not connect
	   directly, but in case they are we assign to root node an UP direction to allow UPDN to discover
	   the subnet correctly (and not from the point of view of the last root node).
	 */
	if (!cur_rank && !rem_rank)
		return UP;

	if (cur_rank < rem_rank)
		return DOWN;
	else if (cur_rank > rem_rank)
		return UP;
	else {
		/* Equal rank, decide by id number, bigger == UP direction */
		if (cur_id > rem_id)
			return UP;
		else
			return DOWN;
	}
}