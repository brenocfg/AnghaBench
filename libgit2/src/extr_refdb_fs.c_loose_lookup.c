#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* gitpath; char* commonpath; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_SYMREF ; 
 scalar_t__ git__prefixcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_rtrim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference__alloc (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference__alloc_symbolic (char const*,char const*) ; 
 scalar_t__ is_per_worktree_ref (char const*) ; 
 int loose_parse_oid (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* loose_parse_symbolic (int /*<<< orphan*/ *) ; 
 int loose_readbuffer (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static int loose_lookup(
	git_reference **out,
	refdb_fs_backend *backend,
	const char *ref_name)
{
	git_buf ref_file = GIT_BUF_INIT;
	int error = 0;
	const char *ref_dir;

	if (out)
		*out = NULL;

	if (is_per_worktree_ref(ref_name))
		ref_dir = backend->gitpath;
	else
		ref_dir = backend->commonpath;

	if ((error = loose_readbuffer(&ref_file, ref_dir, ref_name)) < 0)
		/* cannot read loose ref file - gah */;
	else if (git__prefixcmp(git_buf_cstr(&ref_file), GIT_SYMREF) == 0) {
		const char *target;

		git_buf_rtrim(&ref_file);

		if (!(target = loose_parse_symbolic(&ref_file)))
			error = -1;
		else if (out != NULL)
			*out = git_reference__alloc_symbolic(ref_name, target);
	} else {
		git_oid oid;

		if (!(error = loose_parse_oid(&oid, ref_name, &ref_file)) &&
			out != NULL)
			*out = git_reference__alloc(ref_name, &oid, NULL);
	}

	git_buf_dispose(&ref_file);
	return error;
}