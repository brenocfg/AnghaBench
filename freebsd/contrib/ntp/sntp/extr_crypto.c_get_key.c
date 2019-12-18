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
struct key {int key_id; struct key* next; } ;

/* Variables and functions */
 scalar_t__ key_cnt ; 
 struct key* key_ptr ; 

void
get_key(
	int key_id,
	struct key **d_key
	)
{
	struct key *itr_key;

	if (key_cnt == 0)
		return;
	for (itr_key = key_ptr; itr_key; itr_key = itr_key->next) {
		if (itr_key->key_id == key_id) {
			*d_key = itr_key;
			break;
		}
	}
	return;
}