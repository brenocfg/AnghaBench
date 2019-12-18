#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* data; } ;
struct TYPE_5__ {scalar_t__ val; } ;
struct TYPE_7__ {TYPE_2__ raw; TYPE_1__ refcount; } ;
typedef  TYPE_3__ git_pack_cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (TYPE_3__*) ; 

__attribute__((used)) static void free_cache_object(void *o)
{
	git_pack_cache_entry *e = (git_pack_cache_entry *)o;

	if (e != NULL) {
		assert(e->refcount.val == 0);
		git__free(e->raw.data);
		git__free(e);
	}
}