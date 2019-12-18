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
struct device_node {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  OHARE_FCR ; 
 int /*<<< orphan*/  OH_IDE0_RESET_N ; 
 int /*<<< orphan*/  OH_IDE1_RESET_N ; 
 int /*<<< orphan*/  macio_ohare ; 
 long simple_feature_tweak (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static long ohare_ide_reset(struct device_node *node, long param, long value)
{
	switch(param) {
	case 0:
		return simple_feature_tweak(node, macio_ohare,
			OHARE_FCR, OH_IDE0_RESET_N, !value);
	case 1:
		return simple_feature_tweak(node, macio_ohare,
			OHARE_FCR, OH_IDE1_RESET_N, !value);
	default:
		return -ENODEV;
	}
}