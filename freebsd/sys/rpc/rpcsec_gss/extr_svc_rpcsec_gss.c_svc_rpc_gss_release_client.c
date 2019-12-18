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
struct svc_rpc_gss_client {int /*<<< orphan*/  cl_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_rpc_gss_destroy_client (struct svc_rpc_gss_client*) ; 

__attribute__((used)) static void
svc_rpc_gss_release_client(struct svc_rpc_gss_client *client)
{

	if (!refcount_release(&client->cl_refs))
		return;
	svc_rpc_gss_destroy_client(client);
}