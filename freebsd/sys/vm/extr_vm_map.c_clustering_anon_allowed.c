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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int cluster_anon ; 

__attribute__((used)) static bool
clustering_anon_allowed(vm_offset_t addr)
{

	switch (cluster_anon) {
	case 0:
		return (false);
	case 1:
		return (addr == 0);
	case 2:
	default:
		return (true);
	}
}