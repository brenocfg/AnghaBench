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
 int ENOMEM ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  PF_NAME ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int kproc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_cdevsw ; 
 int /*<<< orphan*/ * pf_dev ; 
 int /*<<< orphan*/  pf_end_lock ; 
 scalar_t__ pf_end_threads ; 
 int /*<<< orphan*/  pf_ioctl_lock ; 
 int /*<<< orphan*/  pf_mtag_initialize () ; 
 int /*<<< orphan*/  pf_purge_proc ; 
 int /*<<< orphan*/  pf_purge_thread ; 
 int /*<<< orphan*/  pf_rules_lock ; 
 int /*<<< orphan*/  pfi_initialize () ; 
 int /*<<< orphan*/  rm_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
pf_load(void)
{
	int error;

	rm_init(&pf_rules_lock, "pf rulesets");
	sx_init(&pf_ioctl_lock, "pf ioctl");
	sx_init(&pf_end_lock, "pf end thread");

	pf_mtag_initialize();

	pf_dev = make_dev(&pf_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600, PF_NAME);
	if (pf_dev == NULL)
		return (ENOMEM);

	pf_end_threads = 0;
	error = kproc_create(pf_purge_thread, NULL, &pf_purge_proc, 0, 0, "pf purge");
	if (error != 0)
		return (error);

	pfi_initialize();

	return (0);
}