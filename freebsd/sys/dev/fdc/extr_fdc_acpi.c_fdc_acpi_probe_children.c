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
struct fdc_walk_ctx {scalar_t__* fd_present; void* acpi_dev; void* dev; scalar_t__ index; } ;
typedef  void* device_t ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 int ACPI_FDC_MAXDEVS ; 
 scalar_t__ ACPI_FD_PRESENT ; 
 int /*<<< orphan*/  ACPI_SCAN_CHILDREN (void*,void*,int,int /*<<< orphan*/ ,struct fdc_walk_ctx*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  bcopy (void*,scalar_t__*,int) ; 
 int bus_generic_attach (void*) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  fdc_acpi_probe_child ; 
 int /*<<< orphan*/ * fdc_add_child (void*,char*,int) ; 
 int /*<<< orphan*/  free (struct fdc_walk_ctx*,int /*<<< orphan*/ ) ; 
 struct fdc_walk_ctx* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdc_acpi_probe_children(device_t bus, device_t dev, void *fde)
{
	struct fdc_walk_ctx *ctx;
	devclass_t fd_dc;
	int i;

	/* Setup the context and walk all child devices. */
	ctx = malloc(sizeof(struct fdc_walk_ctx), M_TEMP, M_NOWAIT);
	if (ctx == NULL) {
		device_printf(dev, "no memory for walking children\n");
		return (ENOMEM);
	}
	bcopy(fde, ctx->fd_present, sizeof(ctx->fd_present));
	ctx->index = 0;
	ctx->dev = dev;
	ctx->acpi_dev = bus;
	ACPI_SCAN_CHILDREN(ctx->acpi_dev, dev, 1, fdc_acpi_probe_child,
	    ctx);

	/* Add any devices not represented by an AML Device handle/node. */
	fd_dc = devclass_find("fd");
	for (i = 0; i < ACPI_FDC_MAXDEVS; i++)
		if (ctx->fd_present[i] == ACPI_FD_PRESENT &&
		    devclass_get_device(fd_dc, i) == NULL) {
			if (fdc_add_child(dev, "fd", i) == NULL)
				device_printf(dev, "fd add failed\n");
		}
	free(ctx, M_TEMP);

	/* Attach any children found during the probe. */
	return (bus_generic_attach(dev));
}