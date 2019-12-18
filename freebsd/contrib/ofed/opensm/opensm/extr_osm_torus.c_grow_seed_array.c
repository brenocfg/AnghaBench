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
struct torus {int seed_cnt; unsigned int seed_sz; int /*<<< orphan*/ * seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 void* realloc (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static
bool grow_seed_array(struct torus *t, int new_seeds)
{
	unsigned cnt;
	void *ptr;

	cnt = t->seed_cnt + new_seeds;
	if (cnt > t->seed_sz) {
		cnt += 2 + cnt / 2;
		ptr = realloc(t->seed, cnt * sizeof(*t->seed));
		if (!ptr)
			return false;
		t->seed = ptr;
		t->seed_sz = cnt;
		memset(&t->seed[t->seed_cnt], 0,
		       (cnt - t->seed_cnt) * sizeof(*t->seed));
	}
	return true;
}