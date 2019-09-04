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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct object_context {int dummy; } ;
typedef  enum get_oid_result { ____Placeholder_get_oid_result } get_oid_result ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 unsigned int GET_OID_FOLLOW_SYMLINKS ; 
 unsigned int GET_OID_ONLY_TO_DIE ; 
 int get_oid_with_context_1 (struct repository*,char const*,unsigned int,int /*<<< orphan*/ *,struct object_id*,struct object_context*) ; 

enum get_oid_result get_oid_with_context(struct repository *repo,
					 const char *str,
					 unsigned flags,
					 struct object_id *oid,
					 struct object_context *oc)
{
	if (flags & GET_OID_FOLLOW_SYMLINKS && flags & GET_OID_ONLY_TO_DIE)
		BUG("incompatible flags for get_sha1_with_context");
	return get_oid_with_context_1(repo, str, flags, NULL, oid, oc);
}