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
struct al_eth_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  al_eth_down (struct al_eth_adapter*) ; 
 struct al_eth_adapter* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
al_shutdown(device_t dev)
{
	struct al_eth_adapter *adapter = device_get_softc(dev);

	al_eth_down(adapter);

	return (0);
}