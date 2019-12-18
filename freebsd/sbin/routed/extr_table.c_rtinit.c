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
struct sockaddr_in {int dummy; } ;
struct ag_info {struct ag_info* ag_fine; } ;

/* Variables and functions */
 int NUM_AG_SLOTS ; 
 void* ag_avail ; 
 void* ag_slots ; 
 int max_keylen ; 
 int /*<<< orphan*/  rhead ; 
 int /*<<< orphan*/  rn_init () ; 
 int /*<<< orphan*/  rn_inithead (int /*<<< orphan*/ *,int) ; 

void
rtinit(void)
{
	int i;
	struct ag_info *ag;

	/* Initialize the radix trees */
	max_keylen = sizeof(struct sockaddr_in);
	rn_init();
	rn_inithead(&rhead, 32);

	/* mark all of the slots in the table free */
	ag_avail = ag_slots;
	for (ag = ag_slots, i = 1; i < NUM_AG_SLOTS; i++) {
		ag->ag_fine = ag+1;
		ag++;
	}
}