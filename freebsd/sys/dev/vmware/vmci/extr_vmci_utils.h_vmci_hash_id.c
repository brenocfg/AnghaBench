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
typedef  unsigned int vmci_id ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */

__attribute__((used)) static inline int
vmci_hash_id(vmci_id id, unsigned size)
{
	unsigned i;
	int hash = 5381;

	for (i = 0; i < sizeof(id); i++)
		hash = ((hash << 5) + hash) + (uint8_t)(id >> (i * 8));

	return (hash & (size - 1));
}