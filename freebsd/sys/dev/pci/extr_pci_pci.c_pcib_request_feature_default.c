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
typedef  enum pci_feature { ____Placeholder_pci_feature } pci_feature ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_REQUEST_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcib_request_feature_default(device_t pcib, device_t dev,
    enum pci_feature feature)
{
	device_t bus;

	/*
	 * Our parent is necessarily a pci bus. Its parent will either be
	 * another pci bridge (which passes it up) or a host bridge that can
	 * approve or reject the request.
	 */
	bus = device_get_parent(pcib);
	return (PCIB_REQUEST_FEATURE(device_get_parent(bus), dev, feature));
}