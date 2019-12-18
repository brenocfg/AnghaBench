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
struct b53_device {scalar_t__ chip_id; } ;

/* Variables and functions */
 scalar_t__ BCM53010_DEVICE_ID ; 
 scalar_t__ BCM53011_DEVICE_ID ; 
 scalar_t__ BCM53012_DEVICE_ID ; 
 scalar_t__ BCM53018_DEVICE_ID ; 
 scalar_t__ BCM53019_DEVICE_ID ; 

__attribute__((used)) static inline int is5301x(struct b53_device *dev)
{
	return dev->chip_id == BCM53010_DEVICE_ID ||
		dev->chip_id == BCM53011_DEVICE_ID ||
		dev->chip_id == BCM53012_DEVICE_ID ||
		dev->chip_id == BCM53018_DEVICE_ID ||
		dev->chip_id == BCM53019_DEVICE_ID;
}