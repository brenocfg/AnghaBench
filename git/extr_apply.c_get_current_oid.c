#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct apply_state {TYPE_2__* repo; } ;
struct TYPE_6__ {TYPE_1__** cache; } ;
struct TYPE_5__ {TYPE_3__* index; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int index_name_pos (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 scalar_t__ read_apply_cache (struct apply_state*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int get_current_oid(struct apply_state *state, const char *path,
			   struct object_id *oid)
{
	int pos;

	if (read_apply_cache(state) < 0)
		return -1;
	pos = index_name_pos(state->repo->index, path, strlen(path));
	if (pos < 0)
		return -1;
	oidcpy(oid, &state->repo->index->cache[pos]->oid);
	return 0;
}