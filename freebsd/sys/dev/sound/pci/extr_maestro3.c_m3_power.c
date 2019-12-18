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
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M3_LOCK_ASSERT (struct sc_info*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
m3_power(struct sc_info *sc, int state)
{
	u_int32_t data;

	M3_DEBUG(CHANGE, ("m3_power(%d)\n", state));
	M3_LOCK_ASSERT(sc);

	data = pci_read_config(sc->dev, 0x34, 1);
	if (pci_read_config(sc->dev, data, 1) == 1) {
		pci_write_config(sc->dev, data + 4, state, 1);
	}

	return 0;
}