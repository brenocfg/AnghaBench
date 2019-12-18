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
struct svc_rpc_gss_client_list {int dummy; } ;
struct TYPE_2__ {size_t ci_id; } ;
struct svc_rpc_gss_client {TYPE_1__ cl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct svc_rpc_gss_client_list*,struct svc_rpc_gss_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_alllink ; 
 int /*<<< orphan*/  cl_link ; 
 int /*<<< orphan*/  svc_rpc_gss_client_count ; 
 struct svc_rpc_gss_client_list* svc_rpc_gss_client_hash ; 
 size_t svc_rpc_gss_client_hash_size ; 
 struct svc_rpc_gss_client_list svc_rpc_gss_clients ; 
 int /*<<< orphan*/  svc_rpc_gss_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svc_rpc_gss_forget_client_locked(struct svc_rpc_gss_client *client)
{
	struct svc_rpc_gss_client_list *list;

	sx_assert(&svc_rpc_gss_lock, SX_XLOCKED);
	list = &svc_rpc_gss_client_hash[client->cl_id.ci_id % svc_rpc_gss_client_hash_size];
	TAILQ_REMOVE(list, client, cl_link);
	TAILQ_REMOVE(&svc_rpc_gss_clients, client, cl_alllink);
	svc_rpc_gss_client_count--;
}