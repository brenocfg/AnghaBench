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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hash (size_t*,int,int,size_t*) ; 

void
ckh_pointer_hash(const void *key, size_t r_hash[2]) {
	union {
		const void	*v;
		size_t		i;
	} u;

	assert(sizeof(u.v) == sizeof(u.i));
	u.v = key;
	hash(&u.i, sizeof(u.i), 0xd983396eU, r_hash);
}