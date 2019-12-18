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
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int IFDI_MEDIA_CHANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_init_locked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iflib_media_change(if_t ifp)
{
	if_ctx_t ctx = if_getsoftc(ifp);
	int err;

	CTX_LOCK(ctx);
	if ((err = IFDI_MEDIA_CHANGE(ctx)) == 0)
		iflib_init_locked(ctx);
	CTX_UNLOCK(ctx);
	return (err);
}