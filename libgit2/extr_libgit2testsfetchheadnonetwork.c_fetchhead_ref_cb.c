#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {unsigned int is_merge; scalar_t__ remote_url; scalar_t__ ref_name; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ git_fetchhead_ref ;
struct TYPE_5__ {int /*<<< orphan*/  idx; int /*<<< orphan*/  fetchhead_vector; } ;
typedef  TYPE_2__ fetchhead_ref_cb_data ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (scalar_t__,char const*) ; 
 TYPE_1__* git_vector_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fetchhead_ref_cb(const char *name, const char *url,
	const git_oid *oid, unsigned int is_merge, void *payload)
{
	fetchhead_ref_cb_data *cb_data = payload;
	git_fetchhead_ref *expected;

	cl_assert(payload);

	expected = git_vector_get(cb_data->fetchhead_vector, cb_data->idx);

	cl_assert_equal_oid(&expected->oid, oid);
	cl_assert(expected->is_merge == is_merge);

	if (expected->ref_name)
		cl_assert_equal_s(expected->ref_name, name);
	else
		cl_assert(name == NULL);

	if (expected->remote_url)
		cl_assert_equal_s(expected->remote_url, url);
	else
		cl_assert(url == NULL);

	cb_data->idx++;

	return 0;
}