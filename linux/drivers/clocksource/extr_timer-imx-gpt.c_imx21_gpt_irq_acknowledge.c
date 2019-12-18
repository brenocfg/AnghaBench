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
struct imx_timer {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MX1_2_TSTAT ; 
 int MX2_TSTAT_CAPT ; 
 int MX2_TSTAT_COMP ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void imx21_gpt_irq_acknowledge(struct imx_timer *imxtm)
{
	writel_relaxed(MX2_TSTAT_CAPT | MX2_TSTAT_COMP,
				imxtm->base + MX1_2_TSTAT);
}