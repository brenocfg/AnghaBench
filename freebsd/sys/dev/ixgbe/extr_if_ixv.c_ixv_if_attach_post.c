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
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixv_add_stats_sysctls (struct adapter*) ; 
 int /*<<< orphan*/  ixv_init_stats (struct adapter*) ; 
 int /*<<< orphan*/  ixv_save_stats (struct adapter*) ; 
 int ixv_setup_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixv_if_attach_post(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	device_t       dev = iflib_get_dev(ctx);
	int            error = 0;

	/* Setup OS specific network interface */
	error = ixv_setup_interface(ctx);
	if (error) {
		device_printf(dev, "Interface setup failed: %d\n", error);
		goto end;
	}

	/* Do the stats setup */
	ixv_save_stats(adapter);
	ixv_init_stats(adapter);
	ixv_add_stats_sysctls(adapter);

end:
	return error;
}