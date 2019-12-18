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
 int /*<<< orphan*/  RIC_FLUSH_ALL ; 
 int /*<<< orphan*/  _tlbie_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_tlbiel_kernel ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tlbie_capable ; 

__attribute__((used)) static inline void _tlbiel_kernel_broadcast(void)
{
	on_each_cpu(do_tlbiel_kernel, NULL, 1);
	if (tlbie_capable) {
		/*
		 * Coherent accelerators don't refcount kernel memory mappings,
		 * so have to always issue a tlbie for them. This is quite a
		 * slow path anyway.
		 */
		_tlbie_pid(0, RIC_FLUSH_ALL);
	}
}