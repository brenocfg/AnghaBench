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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int MDC_PIN (struct mii_bus*) ; 
 int /*<<< orphan*/  gpio_regs ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mdc_hi(struct mii_bus *bus)
{
	out_le32(gpio_regs, 1 << MDC_PIN(bus));
}