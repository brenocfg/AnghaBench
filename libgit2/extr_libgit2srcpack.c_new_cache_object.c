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
typedef  int /*<<< orphan*/  git_rawobj ;
struct TYPE_4__ {int /*<<< orphan*/  raw; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ git_pack_cache_entry ;

/* Variables and functions */
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static git_pack_cache_entry *new_cache_object(git_rawobj *source)
{
	git_pack_cache_entry *e = git__calloc(1, sizeof(git_pack_cache_entry));
	if (!e)
		return NULL;

	git_atomic_inc(&e->refcount);
	memcpy(&e->raw, source, sizeof(git_rawobj));

	return e;
}