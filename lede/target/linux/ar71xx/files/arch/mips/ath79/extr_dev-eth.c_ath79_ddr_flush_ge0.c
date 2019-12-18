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
 int /*<<< orphan*/  ath79_ddr_wb_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath79_ddr_flush_ge0(void)
{
	ath79_ddr_wb_flush(0);
}