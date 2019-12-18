#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/ * repo; } ;
typedef  TYPE_1__ git_object ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

git_repository *git_object_owner(const git_object *obj)
{
	assert(obj);
	return obj->repo;
}