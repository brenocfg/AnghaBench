#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct repository {TYPE_2__* objects; } ;
struct TYPE_4__ {int /*<<< orphan*/ * multi_pack_index; TYPE_1__* odb; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNLEAK (char*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close_midx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_midx_filename (int /*<<< orphan*/ ) ; 
 scalar_t__ remove_path (char*) ; 

void clear_midx_file(struct repository *r)
{
	char *midx = get_midx_filename(r->objects->odb->path);

	if (r->objects && r->objects->multi_pack_index) {
		close_midx(r->objects->multi_pack_index);
		r->objects->multi_pack_index = NULL;
	}

	if (remove_path(midx)) {
		UNLEAK(midx);
		die(_("failed to clear multi-pack-index at %s"), midx);
	}

	free(midx);
}