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
 scalar_t__ ANADIG_REG_2P5 ; 
 int /*<<< orphan*/  BM_ANADIG_REG_2P5_ENABLE_PULLDOWN ; 
 scalar_t__ REG_CLR ; 
 scalar_t__ REG_SET ; 
 int /*<<< orphan*/  anatop ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void imx_anatop_enable_2p5_pulldown(bool enable)
{
	regmap_write(anatop, ANADIG_REG_2P5 + (enable ? REG_SET : REG_CLR),
		BM_ANADIG_REG_2P5_ENABLE_PULLDOWN);
}