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
typedef  int u32 ;
struct arasan_cf_dev {scalar_t__ vbase; } ;

/* Variables and functions */
 int CARD_RESET ; 
 scalar_t__ OP_MODE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void cf_card_reset(struct arasan_cf_dev *acdev)
{
	u32 val = readl(acdev->vbase + OP_MODE);

	writel(val | CARD_RESET, acdev->vbase + OP_MODE);
	udelay(200);
	writel(val & ~CARD_RESET, acdev->vbase + OP_MODE);
}