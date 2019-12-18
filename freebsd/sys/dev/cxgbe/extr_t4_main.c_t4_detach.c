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
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct adapter* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int notify_siblings (int /*<<< orphan*/ ,int) ; 
 int t4_detach_common (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
t4_detach(device_t dev)
{
	struct adapter *sc;
	int rc;

	sc = device_get_softc(dev);

	rc = notify_siblings(dev, 1);
	if (rc) {
		device_printf(dev,
		    "failed to detach sibling devices: %d\n", rc);
		return (rc);
	}

	return (t4_detach_common(dev));
}