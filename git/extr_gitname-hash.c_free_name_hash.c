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
struct index_state {int /*<<< orphan*/  dir_hash; int /*<<< orphan*/  name_hash; scalar_t__ name_hash_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ *,int) ; 

void free_name_hash(struct index_state *istate)
{
	if (!istate->name_hash_initialized)
		return;
	istate->name_hash_initialized = 0;

	hashmap_free(&istate->name_hash, 0);
	hashmap_free(&istate->dir_hash, 1);
}