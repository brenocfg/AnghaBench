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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
witness_hash_djb2(const uint8_t *key, uint32_t size)
{
	unsigned int hash = 5381;
	int i;

	/* hash = hash * 33 + key[i] */
	if (size)
		for (i = 0; i < size; i++)
			hash = ((hash << 5) + hash) + (unsigned int)key[i];
	else
		for (i = 0; key[i] != 0; i++)
			hash = ((hash << 5) + hash) + (unsigned int)key[i];

	return (hash);
}