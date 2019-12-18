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
typedef  int uint16_t ;
struct TYPE_3__ {int id; int index; scalar_t__ in_use; } ;
typedef  TYPE_1__ ocs_queue_hash_t ;
typedef  int int32_t ;

/* Variables and functions */
 int OCS_HW_Q_HASH_SIZE ; 

int32_t
ocs_hw_queue_hash_find(ocs_queue_hash_t *hash, uint16_t id)
{
	int32_t	rc = -1;
	int32_t	index = id & (OCS_HW_Q_HASH_SIZE - 1);

	/*
	 * Since the hash is always bigger than the maximum number of Qs, then we
	 * never have to worry about an infinite loop. We will always find an
	 * unused entry.
	 */
	do {
		if (hash[index].in_use &&
		    hash[index].id == id) {
			rc = hash[index].index;
		} else {
			index = (index + 1) & (OCS_HW_Q_HASH_SIZE - 1);
		}
	} while(rc == -1 && hash[index].in_use);

	return rc;
}