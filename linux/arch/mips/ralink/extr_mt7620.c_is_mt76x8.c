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
 scalar_t__ MT762X_SOC_MT7628AN ; 
 scalar_t__ MT762X_SOC_MT7688 ; 
 scalar_t__ ralink_soc ; 

__attribute__((used)) static inline int is_mt76x8(void)
{
	return ralink_soc == MT762X_SOC_MT7628AN ||
	       ralink_soc == MT762X_SOC_MT7688;
}