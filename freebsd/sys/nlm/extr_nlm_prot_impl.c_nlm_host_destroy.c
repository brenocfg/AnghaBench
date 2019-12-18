#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nr_client; } ;
struct TYPE_3__ {scalar_t__ nr_client; } ;
struct nlm_host {int /*<<< orphan*/  nh_sysctl; int /*<<< orphan*/  nh_lock; TYPE_2__ nh_clntrpc; TYPE_1__ nh_srvrpc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_RELEASE (scalar_t__) ; 
 int /*<<< orphan*/  M_NLM ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nlm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nlm_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nh_link ; 
 int /*<<< orphan*/  nlm_global_lock ; 
 int /*<<< orphan*/  nlm_hosts ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nlm_host_destroy(struct nlm_host *host)
{

	mtx_lock(&nlm_global_lock);
	TAILQ_REMOVE(&nlm_hosts, host, nh_link);
	mtx_unlock(&nlm_global_lock);

	if (host->nh_srvrpc.nr_client)
		CLNT_RELEASE(host->nh_srvrpc.nr_client);
	if (host->nh_clntrpc.nr_client)
		CLNT_RELEASE(host->nh_clntrpc.nr_client);
	mtx_destroy(&host->nh_lock);
	sysctl_ctx_free(&host->nh_sysctl);
	free(host, M_NLM);
}