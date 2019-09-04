#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ git_cached_obj ;

/* Variables and functions */
#define  GIT_CACHE_STORE_PARSED 129 
#define  GIT_CACHE_STORE_RAW 128 
 int /*<<< orphan*/  git__free (void*) ; 
 scalar_t__ git_atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object__free (void*) ; 
 int /*<<< orphan*/  git_odb_object__free (void*) ; 

void git_cached_obj_decref(void *_obj)
{
	git_cached_obj *obj = _obj;

	if (git_atomic_dec(&obj->refcount) == 0) {
		switch (obj->flags) {
		case GIT_CACHE_STORE_RAW:
			git_odb_object__free(_obj);
			break;

		case GIT_CACHE_STORE_PARSED:
			git_object__free(_obj);
			break;

		default:
			git__free(_obj);
			break;
		}
	}
}