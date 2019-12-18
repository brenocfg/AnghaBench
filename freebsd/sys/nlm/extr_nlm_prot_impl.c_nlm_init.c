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
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NLM_ERR (char*) ; 
 int /*<<< orphan*/  SY_THR_STATIC_KLD ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_global_lock ; 
 int /*<<< orphan*/  nlm_hosts ; 
 int /*<<< orphan*/  nlm_syscalls ; 
 int /*<<< orphan*/  nlm_waiting_locks ; 
 int syscall_helper_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nlm_init(void)
{
	int error;

	mtx_init(&nlm_global_lock, "nlm_global_lock", NULL, MTX_DEF);
	TAILQ_INIT(&nlm_waiting_locks);
	TAILQ_INIT(&nlm_hosts);

	error = syscall_helper_register(nlm_syscalls, SY_THR_STATIC_KLD);
	if (error != 0)
		NLM_ERR("Can't register NLM syscall\n");
	return (error);
}