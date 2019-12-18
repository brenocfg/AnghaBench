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
struct test_probe {int registered; int hit; int /*<<< orphan*/  kprobe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int register_kprobe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int register_test_probe(struct test_probe *probe)
{
	int ret;

	if (probe->registered)
		BUG();

	ret = register_kprobe(&probe->kprobe);
	if (ret >= 0) {
		probe->registered = true;
		probe->hit = -1;
	}
	return ret;
}