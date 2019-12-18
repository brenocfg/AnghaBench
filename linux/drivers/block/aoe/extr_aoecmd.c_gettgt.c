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
struct aoetgt {int /*<<< orphan*/  addr; } ;
struct aoedev {int ntargets; struct aoetgt** targets; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct aoetgt *
gettgt(struct aoedev *d, char *addr)
{
	struct aoetgt **t, **e;

	t = d->targets;
	e = t + d->ntargets;
	for (; t < e && *t; t++)
		if (memcmp((*t)->addr, addr, sizeof((*t)->addr)) == 0)
			return *t;
	return NULL;
}