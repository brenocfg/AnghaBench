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
 int RPC_GSS_HASH_SIZE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_gss_all ; 
 int /*<<< orphan*/ * rpc_gss_cache ; 
 int /*<<< orphan*/  rpc_gss_lock ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
rpc_gss_hashinit(void *dummy)
{
	int i;

	for (i = 0; i < RPC_GSS_HASH_SIZE; i++)
		TAILQ_INIT(&rpc_gss_cache[i]);
	TAILQ_INIT(&rpc_gss_all);
	sx_init(&rpc_gss_lock, "rpc_gss_lock");
}