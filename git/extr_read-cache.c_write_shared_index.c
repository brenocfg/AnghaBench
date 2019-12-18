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
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct tempfile {TYPE_1__ filename; } ;
struct split_index {TYPE_2__* base; int /*<<< orphan*/  base_oid; } ;
struct index_state {struct split_index* split_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int adjust_shared_perm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_shared_index_files (int /*<<< orphan*/ ) ; 
 int do_write_index (TYPE_2__*,struct tempfile*,int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tempfile_path (struct tempfile*) ; 
 int /*<<< orphan*/  git_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_cache_to_base_index (struct index_state*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rename_tempfile (struct tempfile**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace2_region_enter_printf (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_region_leave_printf (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_shared_index(struct index_state *istate,
			      struct tempfile **temp)
{
	struct split_index *si = istate->split_index;
	int ret;

	move_cache_to_base_index(istate);

	trace2_region_enter_printf("index", "shared/do_write_index",
				   the_repository, "%s", (*temp)->filename.buf);
	ret = do_write_index(si->base, *temp, 1);
	trace2_region_leave_printf("index", "shared/do_write_index",
				   the_repository, "%s", (*temp)->filename.buf);

	if (ret)
		return ret;
	ret = adjust_shared_perm(get_tempfile_path(*temp));
	if (ret) {
		error(_("cannot fix permission bits on '%s'"), get_tempfile_path(*temp));
		return ret;
	}
	ret = rename_tempfile(temp,
			      git_path("sharedindex.%s", oid_to_hex(&si->base->oid)));
	if (!ret) {
		oidcpy(&si->base_oid, &si->base->oid);
		clean_shared_index_files(oid_to_hex(&si->base->oid));
	}

	return ret;
}