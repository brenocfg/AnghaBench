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
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  reflog_expiry_should_prune_fn ;
typedef  int /*<<< orphan*/  reflog_expiry_prepare_fn ;
typedef  int /*<<< orphan*/  reflog_expiry_cleanup_fn ;

/* Variables and functions */
 int /*<<< orphan*/  get_main_ref_store (int /*<<< orphan*/ ) ; 
 int refs_reflog_expire (int /*<<< orphan*/ ,char const*,struct object_id const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  the_repository ; 

int reflog_expire(const char *refname, const struct object_id *oid,
		  unsigned int flags,
		  reflog_expiry_prepare_fn prepare_fn,
		  reflog_expiry_should_prune_fn should_prune_fn,
		  reflog_expiry_cleanup_fn cleanup_fn,
		  void *policy_cb_data)
{
	return refs_reflog_expire(get_main_ref_store(the_repository),
				  refname, oid, flags,
				  prepare_fn, should_prune_fn,
				  cleanup_fn, policy_cb_data);
}