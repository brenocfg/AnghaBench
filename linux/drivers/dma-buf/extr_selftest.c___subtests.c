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
struct subtest {int (* func ) (void*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  apply_subtest_filter (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int stub1 (void*) ; 

int
__subtests(const char *caller, const struct subtest *st, int count, void *data)
{
	int err;

	for (; count--; st++) {
		cond_resched();
		if (signal_pending(current))
			return -EINTR;

		if (!apply_subtest_filter(caller, st->name))
			continue;

		pr_info("dma-buf: Running %s/%s\n", caller, st->name);

		err = st->func(data);
		if (err && err != -EINTR) {
			pr_err("dma-buf/%s: %s failed with error %d\n",
			       caller, st->name, err);
			return err;
		}
	}

	return 0;
}