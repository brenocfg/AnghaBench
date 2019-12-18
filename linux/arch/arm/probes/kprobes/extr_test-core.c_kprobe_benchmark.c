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
struct kprobe {int /*<<< orphan*/  pre_handler; int /*<<< orphan*/ * addr; } ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 int benchmark (void (*) ()) ; 
 int /*<<< orphan*/  benchmark_pre_handler ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int register_kprobe (struct kprobe*) ; 
 int /*<<< orphan*/  unregister_kprobe (struct kprobe*) ; 

__attribute__((used)) static int kprobe_benchmark(void(*fn)(void), unsigned offset)
{
	struct kprobe k = {
		.addr		= (kprobe_opcode_t *)((uintptr_t)fn + offset),
		.pre_handler	= benchmark_pre_handler,
	};

	int ret = register_kprobe(&k);
	if (ret < 0) {
		pr_err("FAIL: register_kprobe failed with %d\n", ret);
		return ret;
	}

	ret = benchmark(fn);

	unregister_kprobe(&k);
	return ret;
}