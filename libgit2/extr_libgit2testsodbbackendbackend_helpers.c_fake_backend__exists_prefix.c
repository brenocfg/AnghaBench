#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ fake_object ;
struct TYPE_6__ {int /*<<< orphan*/  exists_prefix_calls; } ;
typedef  TYPE_2__ fake_backend ;

/* Variables and functions */
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int search_object (TYPE_1__ const**,TYPE_2__*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int fake_backend__exists_prefix(
	git_oid *out, git_odb_backend *backend, const git_oid *oid, size_t len)
{
	const fake_object *obj;
	fake_backend *fake;
	int error;

	fake = (fake_backend *)backend;

	fake->exists_prefix_calls++;

	if ((error = search_object(&obj, fake, oid, len)) < 0)
		return error;

	if (out)
		git_oid_fromstr(out, obj->oid);

	return 0;
}