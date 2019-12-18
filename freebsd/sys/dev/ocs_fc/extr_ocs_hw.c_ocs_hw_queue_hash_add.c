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
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int in_use; int id; int index; } ;
typedef  TYPE_1__ ocs_queue_hash_t ;

/* Variables and functions */
 int OCS_HW_Q_HASH_SIZE ; 

__attribute__((used)) static void
ocs_hw_queue_hash_add(ocs_queue_hash_t *hash, uint16_t id, uint16_t index)
{
	uint32_t	hash_index = id & (OCS_HW_Q_HASH_SIZE - 1);

	/*
	 * Since the hash is always bigger than the number of queues, then we
	 * never have to worry about an infinite loop.
	 */
	while(hash[hash_index].in_use) {
		hash_index = (hash_index + 1) & (OCS_HW_Q_HASH_SIZE - 1);
	}

	/* not used, claim the entry */
	hash[hash_index].id = id;
	hash[hash_index].in_use = 1;
	hash[hash_index].index = index;
}