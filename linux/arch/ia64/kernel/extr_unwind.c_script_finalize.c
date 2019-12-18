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
struct unw_state_record {int /*<<< orphan*/  pr_val; int /*<<< orphan*/  pr_mask; } ;
struct unw_script {int /*<<< orphan*/  pr_val; int /*<<< orphan*/  pr_mask; } ;

/* Variables and functions */

__attribute__((used)) static void
script_finalize (struct unw_script *script, struct unw_state_record *sr)
{
	script->pr_mask = sr->pr_mask;
	script->pr_val = sr->pr_val;
	/*
	 * We could down-grade our write-lock on script->lock here but
	 * the rwlock API doesn't offer atomic lock downgrading, so
	 * we'll just keep the write-lock and release it later when
	 * we're done using the script.
	 */
}