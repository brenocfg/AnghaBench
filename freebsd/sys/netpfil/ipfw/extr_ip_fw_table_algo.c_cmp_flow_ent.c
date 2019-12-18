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
typedef  scalar_t__ uint64_t ;
struct fhashentry {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 scalar_t__ memcmp (struct fhashentry*,struct fhashentry*,size_t) ; 

__attribute__((used)) static __inline int
cmp_flow_ent(struct fhashentry *a, struct fhashentry *b, size_t sz)
{
	uint64_t *ka, *kb;

	ka = (uint64_t *)(&a->next + 1);
	kb = (uint64_t *)(&b->next + 1);

	if (*ka == *kb && (memcmp(a + 1, b + 1, sz) == 0))
		return (1);

	return (0);
}