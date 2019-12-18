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
 scalar_t__ ISC_FALSE ; 
 int /*<<< orphan*/  cleanup_managers () ; 
 int /*<<< orphan*/ * ectx ; 
 scalar_t__ hash_active ; 
 int /*<<< orphan*/  isc_entropy_detach (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_hash_destroy () ; 
 int /*<<< orphan*/  isc_log_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_mem_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_taskmgr_destroy (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * lctx ; 
 int /*<<< orphan*/ * mctx ; 
 int /*<<< orphan*/ * taskmgr ; 

void
isc_test_end() {
	if (taskmgr != NULL)
		isc_taskmgr_destroy(&taskmgr);
	if (lctx != NULL)
		isc_log_destroy(&lctx);
	if (hash_active) {
		isc_hash_destroy();
		hash_active = ISC_FALSE;
	}
	if (ectx != NULL)
		isc_entropy_detach(&ectx);

	cleanup_managers();

	if (mctx != NULL)
		isc_mem_destroy(&mctx);
}