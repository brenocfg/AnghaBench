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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int isa_get_vendorid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnpmss_ids ; 

__attribute__((used)) static int
pnpmss_probe(device_t dev)
{
	u_int32_t lid, vid;

	lid = isa_get_logicalid(dev);
	vid = isa_get_vendorid(dev);
	if (lid == 0x01000000 && vid != 0x0100a90d) /* CMI0001 */
		return ENXIO;
	return ISA_PNP_PROBE(device_get_parent(dev), dev, pnpmss_ids);
}