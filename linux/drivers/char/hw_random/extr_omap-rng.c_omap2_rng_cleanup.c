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
struct omap_rng_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNG_SYSCONFIG_REG ; 
 int /*<<< orphan*/  omap_rng_write (struct omap_rng_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap2_rng_cleanup(struct omap_rng_dev *priv)
{
	omap_rng_write(priv, RNG_SYSCONFIG_REG, 0x0);
}