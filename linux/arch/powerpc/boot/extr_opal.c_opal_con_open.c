#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  kentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  opal_kentry ; 
 TYPE_1__ platform_ops ; 

__attribute__((used)) static int opal_con_open(void)
{
	/*
	 * When OPAL loads the boot kernel it stashes the OPAL base and entry
	 * address in r8 and r9 so the kernel can use the OPAL console
	 * before unflattening the devicetree. While executing the wrapper will
	 * probably trash r8 and r9 so this kentry hook restores them before
	 * entering the decompressed kernel.
	 */
	platform_ops.kentry = opal_kentry;
	return 0;
}