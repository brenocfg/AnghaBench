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
typedef  int uint32_t ;

/* Variables and functions */
 int le32toh (int const) ; 
 int rol32 (int,int) ; 

uint32_t
murmur3_32_hash32(const uint32_t *data, size_t count, uint32_t seed)
{
	uint32_t hash, k;
	size_t res;

	/* iterate */
	for (res = count, hash = seed; res > 0; res--, data++) {
		k = le32toh(*data);
		k *= 0xcc9e2d51;
		k = rol32(k, 15);
		k *= 0x1b873593;
		hash ^= k;
		hash = rol32(hash, 13);
		hash *= 5;
		hash += 0xe6546b64;
	}

	/* finalize */
	hash ^= (uint32_t)count;
	hash ^= hash >> 16;
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;
	return (hash);
}