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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFC_INIT_DONE ; 
 int IFDI_DETACH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int iflib_get_flags (int /*<<< orphan*/ ) ; 

int
iflib_pseudo_detach(device_t dev)
{
	if_ctx_t ctx;
	uint32_t ifc_flags;

	ctx = device_get_softc(dev);
	ifc_flags = iflib_get_flags(ctx);
	if ((ifc_flags & IFC_INIT_DONE) == 0)
		return (0);
	return (IFDI_DETACH(ctx));
}