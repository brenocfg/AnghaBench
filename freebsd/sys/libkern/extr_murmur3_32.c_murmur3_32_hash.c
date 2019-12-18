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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int le32dec (int const*) ; 
 int rol32 (int,int) ; 

uint32_t
murmur3_32_hash(const void *data, size_t len, uint32_t seed)
{
	const uint8_t *bytes;
	uint32_t hash, k;
	size_t res;

	/* initialization */
	bytes = data;
	res = len;
	hash = seed;

	/* main loop */
	while (res >= 4) {
		/* replace with le32toh() if input is aligned */
		k = le32dec(bytes);
		bytes += 4;
		res -= 4;
		k *= 0xcc9e2d51;
		k = rol32(k, 15);
		k *= 0x1b873593;
		hash ^= k;
		hash = rol32(hash, 13);
		hash *= 5;
		hash += 0xe6546b64;
	}

	/* remainder */
	/* remove if input length is a multiple of 4 */
	if (res > 0) {
		k = 0;
		switch (res) {
		case 3:
			k |= bytes[2] << 16;
		case 2:
			k |= bytes[1] << 8;
		case 1:
			k |= bytes[0];
			k *= 0xcc9e2d51;
			k = rol32(k, 15);
			k *= 0x1b873593;
			hash ^= k;
			break;
		}
	}

	/* finalize */
	hash ^= (uint32_t)len;
	hash ^= hash >> 16;
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;
	return (hash);
}