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
struct selftest {int (* func ) () ;int /*<<< orphan*/  name; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int ENOTTY ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_default_test_all (struct selftest*,unsigned long) ; 
 int stub1 () ; 

__attribute__((used)) static int run_selftests(struct selftest *st, unsigned long count)
{
	int err = 0;

	set_default_test_all(st, count);

	/* Tests are listed in natural order in selftests.h */
	for (; count--; st++) {
		if (!st->enabled)
			continue;

		pr_info("dma-buf: Running %s\n", st->name);
		err = st->func();
		if (err)
			break;
	}

	if (WARN(err > 0 || err == -ENOTTY,
		 "%s returned %d, conflicting with selftest's magic values!\n",
		 st->name, err))
		err = -1;

	return err;
}