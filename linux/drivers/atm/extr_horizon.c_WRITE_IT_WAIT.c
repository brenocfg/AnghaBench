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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_0_REG ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wr_regl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void WRITE_IT_WAIT (const hrz_dev *dev, u32 ctrl)
{
	wr_regl (dev, CONTROL_0_REG, ctrl);
	udelay (5);
}