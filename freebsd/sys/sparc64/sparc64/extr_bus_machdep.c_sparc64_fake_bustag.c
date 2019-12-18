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
struct bus_space_tag {int bst_type; int /*<<< orphan*/ * bst_cookie; } ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */

bus_space_handle_t
sparc64_fake_bustag(int space, bus_addr_t addr, struct bus_space_tag *ptag)
{

	ptag->bst_cookie = NULL;
	ptag->bst_type = space;
	return (addr);
}