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
struct sx {int dummy; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_getsoftc (int /*<<< orphan*/ ) ; 
 struct sx* iflib_ctx_lock_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_pseudo_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_pseudodev ; 
 int /*<<< orphan*/  iflib_set_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (struct sx*) ; 
 int /*<<< orphan*/  sx_xunlock (struct sx*) ; 

__attribute__((used)) static void
iflib_clone_destroy(if_t ifp)
{
	if_ctx_t ctx;
	device_t dev;
	struct sx *ctx_lock;
	int rc;

	/*
	 * Detach device / free / free unit 
	 */
	ctx = if_getsoftc(ifp);
	dev = iflib_get_dev(ctx);
	ctx_lock = iflib_ctx_lock_get(ctx);
	sx_xlock(ctx_lock);
	iflib_set_detach(ctx);
	iflib_stop(ctx);
	sx_xunlock(ctx_lock);

	mtx_lock(&Giant);
	rc = device_delete_child(iflib_pseudodev, dev);
	mtx_unlock(&Giant);
	if (rc == 0)
		iflib_pseudo_deregister(ctx);
}