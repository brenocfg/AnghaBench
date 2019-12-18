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
 int /*<<< orphan*/  JQUEUE_LOCK_DESTROY () ; 
 int /*<<< orphan*/  nat64lsn_aliaslink_zone ; 
 int /*<<< orphan*/  nat64lsn_host_zone ; 
 int /*<<< orphan*/  nat64lsn_job_zone ; 
 int /*<<< orphan*/  nat64lsn_pg_zone ; 
 int /*<<< orphan*/  nat64lsn_pgchunk_zone ; 
 int /*<<< orphan*/  nat64lsn_state_zone ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

void
nat64lsn_uninit_internal(void)
{

	/* XXX: epoch_task drain */
	JQUEUE_LOCK_DESTROY();
	uma_zdestroy(nat64lsn_host_zone);
	uma_zdestroy(nat64lsn_pgchunk_zone);
	uma_zdestroy(nat64lsn_pg_zone);
	uma_zdestroy(nat64lsn_aliaslink_zone);
	uma_zdestroy(nat64lsn_state_zone);
	uma_zdestroy(nat64lsn_job_zone);
}