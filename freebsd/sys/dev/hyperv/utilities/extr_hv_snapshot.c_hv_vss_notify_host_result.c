#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct hv_vss_req_internal {TYPE_1__* sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  hv_vss_notify_host_result_locked (struct hv_vss_req_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hv_vss_notify_host_result(struct hv_vss_req_internal *reqp, uint32_t status)
{
	mtx_lock(&reqp->sc->pending_mutex);
	hv_vss_notify_host_result_locked(reqp, status);
	mtx_unlock(&reqp->sc->pending_mutex);
}