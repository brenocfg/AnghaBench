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
 int /*<<< orphan*/  L2X0_CLEAN_INV_WAY ; 
 int /*<<< orphan*/  l2c220_op_way (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2x0_base ; 

__attribute__((used)) static void l2c220_flush_all(void)
{
	l2c220_op_way(l2x0_base, L2X0_CLEAN_INV_WAY);
}