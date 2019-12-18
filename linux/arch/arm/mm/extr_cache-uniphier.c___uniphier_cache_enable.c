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
struct uniphier_cache_data {scalar_t__ ctrl_base; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_SSCC ; 
 int UNIPHIER_SSCC_ON ; 
 int UNIPHIER_SSCC_PRD ; 
 int UNIPHIER_SSCC_WTG ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void __uniphier_cache_enable(struct uniphier_cache_data *data, bool on)
{
	u32 val = 0;

	if (on)
		val = UNIPHIER_SSCC_WTG | UNIPHIER_SSCC_PRD | UNIPHIER_SSCC_ON;

	writel_relaxed(val, data->ctrl_base + UNIPHIER_SSCC);
}