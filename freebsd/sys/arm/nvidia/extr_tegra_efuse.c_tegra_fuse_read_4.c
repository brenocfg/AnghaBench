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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  RD4 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dev_sc ; 
 int /*<<< orphan*/  panic (char*) ; 

uint32_t
tegra_fuse_read_4(int addr) {

	if (dev_sc == NULL)
		panic("tegra_fuse_read_4 called too early");
	return (RD4(dev_sc, addr));
}