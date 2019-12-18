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
struct repository {TYPE_1__* objects; } ;
struct object_directory {int /*<<< orphan*/  path; struct object_directory* next; } ;
struct TYPE_2__ {int packed_git_initialized; struct object_directory* odb; } ;

/* Variables and functions */
 int /*<<< orphan*/  prepare_alt_odb (struct repository*) ; 
 int /*<<< orphan*/  prepare_multi_pack_index_one (struct repository*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prepare_packed_git_mru (struct repository*) ; 
 int /*<<< orphan*/  prepare_packed_git_one (struct repository*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rearrange_packed_git (struct repository*) ; 

__attribute__((used)) static void prepare_packed_git(struct repository *r)
{
	struct object_directory *odb;

	if (r->objects->packed_git_initialized)
		return;

	prepare_alt_odb(r);
	for (odb = r->objects->odb; odb; odb = odb->next) {
		int local = (odb == r->objects->odb);
		prepare_multi_pack_index_one(r, odb->path, local);
		prepare_packed_git_one(r, odb->path, local);
	}
	rearrange_packed_git(r);

	prepare_packed_git_mru(r);
	r->objects->packed_git_initialized = 1;
}