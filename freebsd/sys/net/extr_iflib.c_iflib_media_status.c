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
struct ifmediareq {int dummy; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFDI_MEDIA_STATUS (int /*<<< orphan*/ ,struct ifmediareq*) ; 
 int /*<<< orphan*/  IFDI_UPDATE_ADMIN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_getsoftc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iflib_media_status(if_t ifp, struct ifmediareq *ifmr)
{
	if_ctx_t ctx = if_getsoftc(ifp);

	CTX_LOCK(ctx);
	IFDI_UPDATE_ADMIN_STATUS(ctx);
	IFDI_MEDIA_STATUS(ctx, ifmr);
	CTX_UNLOCK(ctx);
}