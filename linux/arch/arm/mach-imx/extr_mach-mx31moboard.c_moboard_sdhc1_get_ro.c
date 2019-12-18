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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHC1_WP ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int moboard_sdhc1_get_ro(struct device *dev)
{
	return !gpio_get_value(SDHC1_WP);
}