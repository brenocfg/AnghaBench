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
typedef  int /*<<< orphan*/  vm_page_t ;

/* Variables and functions */
 int mtx_trylock_flags_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  vm_page_lockptr (int /*<<< orphan*/ ) ; 

int
vm_page_trylock_KBI(vm_page_t m, const char *file, int line)
{

	return (mtx_trylock_flags_(vm_page_lockptr(m), 0, file, line));
}