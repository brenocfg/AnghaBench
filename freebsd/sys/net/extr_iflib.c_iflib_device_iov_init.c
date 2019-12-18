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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int IFDI_IOV_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 

int
iflib_device_iov_init(device_t dev, uint16_t num_vfs, const nvlist_t *params)
{
	int error;
	if_ctx_t ctx = device_get_softc(dev);

	CTX_LOCK(ctx);
	error = IFDI_IOV_INIT(ctx, num_vfs, params);
	CTX_UNLOCK(ctx);

	return (error);
}