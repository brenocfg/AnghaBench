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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ahci_ctlr_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ahci_gen_ctlr_reset(device_t dev)
{

	return ahci_ctlr_reset(dev);
}