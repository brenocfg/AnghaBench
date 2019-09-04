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
struct annotated_commit_cb_data {size_t i; int /*<<< orphan*/ * oid_str; } ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int annotated_commit_foreach_cb(const git_oid *oid, void *payload)
{
	git_oid expected_oid;
	struct annotated_commit_cb_data *cb_data = payload;

	git_oid_fromstr(&expected_oid, cb_data->oid_str[cb_data->i]);
	cl_assert(git_oid_cmp(&expected_oid, oid) == 0);
	cb_data->i++;
	return 0;
}