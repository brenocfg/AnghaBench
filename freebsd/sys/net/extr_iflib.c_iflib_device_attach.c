#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_shared_ctx_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ isc_magic; } ;

/* Variables and functions */
 TYPE_1__* DEVICE_REGISTER (int /*<<< orphan*/ ) ; 
 int ENOTSUP ; 
 scalar_t__ IFLIB_MAGIC ; 
 int iflib_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 

int
iflib_device_attach(device_t dev)
{
	if_ctx_t ctx;
	if_shared_ctx_t sctx;

	if ((sctx = DEVICE_REGISTER(dev)) == NULL || sctx->isc_magic != IFLIB_MAGIC)
		return (ENOTSUP);

	pci_enable_busmaster(dev);

	return (iflib_device_register(dev, NULL, sctx, &ctx));
}