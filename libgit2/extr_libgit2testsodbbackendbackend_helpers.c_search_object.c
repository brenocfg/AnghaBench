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
struct TYPE_5__ {scalar_t__ oid; } ;
typedef  TYPE_1__ fake_object ;
struct TYPE_6__ {TYPE_1__* objects; } ;
typedef  TYPE_2__ fake_backend ;

/* Variables and functions */
 int GIT_EAMBIGUOUS ; 
 int GIT_ENOTFOUND ; 
 int GIT_OK ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ git_oid_ncmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int search_object(const fake_object **out, fake_backend *fake, const git_oid *oid, size_t len)
{
	const fake_object *obj = fake->objects, *found = NULL;

	while (obj && obj->oid) {
		git_oid current_oid;

		git_oid_fromstr(&current_oid, obj->oid);

		if (git_oid_ncmp(&current_oid, oid, len) == 0) {
			if (found)
				return GIT_EAMBIGUOUS;
			found = obj;
		}

		obj++;
	}

	if (found && out)
		*out = found;

	return found ? GIT_OK : GIT_ENOTFOUND;
}