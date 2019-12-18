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

/* Variables and functions */
 int CLIENT_HASH_SIZE ; 
 int /*<<< orphan*/  RPCSEC_GSS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svc_auth_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rpc_gss ; 
 int /*<<< orphan*/ * svc_rpc_gss_client_hash ; 
 int /*<<< orphan*/  svc_rpc_gss_clients ; 
 scalar_t__ svc_rpc_gss_initialised ; 

__attribute__((used)) static void
svc_rpc_gss_init(void)
{
	int i;

	if (!svc_rpc_gss_initialised) {
		for (i = 0; i < CLIENT_HASH_SIZE; i++)
			TAILQ_INIT(&svc_rpc_gss_client_hash[i]);
		TAILQ_INIT(&svc_rpc_gss_clients);
		svc_auth_reg(RPCSEC_GSS, svc_rpc_gss);
		svc_rpc_gss_initialised = TRUE;
	}
}