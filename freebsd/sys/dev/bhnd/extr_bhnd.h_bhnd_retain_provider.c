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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_service_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_BUS_RETAIN_PROVIDER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline device_t
bhnd_retain_provider(device_t dev, bhnd_service_t service)
{
	return (BHND_BUS_RETAIN_PROVIDER(device_get_parent(dev), dev,
	    service));
}