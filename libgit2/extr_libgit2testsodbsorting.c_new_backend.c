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
typedef  int /*<<< orphan*/  git_odb_backend ;
struct TYPE_4__ {void (* free ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  version; } ;
struct TYPE_5__ {size_t position; TYPE_1__ base; } ;
typedef  TYPE_2__ fake_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ODB_BACKEND_VERSION ; 
 TYPE_2__* git__calloc (int,int) ; 
 scalar_t__ git__free ; 

__attribute__((used)) static git_odb_backend *new_backend(size_t position)
{
	fake_backend *b;

	b = git__calloc(1, sizeof(fake_backend));
	if (b == NULL)
		return NULL;

	b->base.free = (void (*)(git_odb_backend *)) git__free;
	b->base.version = GIT_ODB_BACKEND_VERSION;
	b->position = position;
	return (git_odb_backend *)b;
}