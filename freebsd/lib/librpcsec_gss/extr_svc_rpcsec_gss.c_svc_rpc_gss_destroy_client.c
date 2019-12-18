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
struct svc_rpc_gss_client_list {int dummy; } ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {struct svc_rpc_gss_client* client_principal; } ;
struct svc_rpc_gss_client {int len; size_t cl_id; TYPE_2__ cl_verf; TYPE_1__ cl_rawcred; int /*<<< orphan*/  cl_cname; int /*<<< orphan*/  cl_ctx; } ;
typedef  int /*<<< orphan*/  OM_uint32 ;

/* Variables and functions */
 size_t CLIENT_HASH_SIZE ; 
 int /*<<< orphan*/  GSS_C_NO_BUFFER ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct svc_rpc_gss_client_list*,struct svc_rpc_gss_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_alllink ; 
 int /*<<< orphan*/  cl_link ; 
 int /*<<< orphan*/  gss_delete_sec_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gss_release_buffer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  gss_release_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  mem_free (struct svc_rpc_gss_client*,int) ; 
 int /*<<< orphan*/  svc_rpc_gss_client_count ; 
 struct svc_rpc_gss_client_list* svc_rpc_gss_client_hash ; 
 struct svc_rpc_gss_client_list svc_rpc_gss_clients ; 

__attribute__((used)) static void
svc_rpc_gss_destroy_client(struct svc_rpc_gss_client *client)
{
	struct svc_rpc_gss_client_list *list;
	OM_uint32 min_stat;

	log_debug("in svc_rpc_gss_destroy_client()");

	if (client->cl_ctx)
		gss_delete_sec_context(&min_stat,
		    &client->cl_ctx, GSS_C_NO_BUFFER);

	if (client->cl_cname)
		gss_release_name(&min_stat, &client->cl_cname);

	if (client->cl_rawcred.client_principal)
		mem_free(client->cl_rawcred.client_principal,
		    sizeof(*client->cl_rawcred.client_principal)
		    + client->cl_rawcred.client_principal->len);

	if (client->cl_verf.value)
		gss_release_buffer(&min_stat, &client->cl_verf);

	list = &svc_rpc_gss_client_hash[client->cl_id % CLIENT_HASH_SIZE];
	TAILQ_REMOVE(list, client, cl_link);
	TAILQ_REMOVE(&svc_rpc_gss_clients, client, cl_alllink);
	svc_rpc_gss_client_count--;
	mem_free(client, sizeof(*client));
}