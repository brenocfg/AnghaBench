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
struct rand_data {unsigned int data; } ;
typedef  unsigned int __u64 ;

/* Variables and functions */
 unsigned int DATA_SIZE_BITS ; 
 int /*<<< orphan*/  jent_get_nstime (unsigned int*) ; 

__attribute__((used)) static __u64 jent_loop_shuffle(struct rand_data *ec,
			       unsigned int bits, unsigned int min)
{
	__u64 time = 0;
	__u64 shuffle = 0;
	unsigned int i = 0;
	unsigned int mask = (1<<bits) - 1;

	jent_get_nstime(&time);
	/*
	 * Mix the current state of the random number into the shuffle
	 * calculation to balance that shuffle a bit more.
	 */
	if (ec)
		time ^= ec->data;
	/*
	 * We fold the time value as much as possible to ensure that as many
	 * bits of the time stamp are included as possible.
	 */
	for (i = 0; ((DATA_SIZE_BITS + bits - 1) / bits) > i; i++) {
		shuffle ^= time & mask;
		time = time >> bits;
	}

	/*
	 * We add a lower boundary value to ensure we have a minimum
	 * RNG loop count.
	 */
	return (shuffle + (1<<min));
}