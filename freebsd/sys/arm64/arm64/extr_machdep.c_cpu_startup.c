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
 int /*<<< orphan*/  bufinit () ; 
 int /*<<< orphan*/  identify_cpu () ; 
 int /*<<< orphan*/  install_cpu_errata () ; 
 int /*<<< orphan*/  kmi ; 
 int /*<<< orphan*/  undef_init () ; 
 int /*<<< orphan*/  vm_ksubmap_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_bufferinit () ; 

__attribute__((used)) static void
cpu_startup(void *dummy)
{

	undef_init();
	identify_cpu();
	install_cpu_errata();

	vm_ksubmap_init(&kmi);
	bufinit();
	vm_pager_bufferinit();
}