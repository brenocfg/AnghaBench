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
struct sc_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALL ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  m3_power (struct sc_info*,int) ; 
 struct sc_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
m3_pci_shutdown(device_t dev)
{
	struct sc_info *sc = pcm_getdevinfo(dev);

	M3_DEBUG(CALL, ("m3_pci_shutdown\n"));

	M3_LOCK(sc);
	m3_power(sc, 3); /* power off */
	M3_UNLOCK(sc);

	return 0;
}