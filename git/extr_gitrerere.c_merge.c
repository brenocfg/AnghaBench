#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rerere_id {int dummy; } ;
struct index_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ mmfile_t ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ mmbuffer_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ handle_file (struct index_state*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ read_mmfile (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rerere_path (struct rerere_id const*,char*) ; 
 int try_merge (struct index_state*,struct rerere_id const*,char const*,TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ utime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int merge(struct index_state *istate, const struct rerere_id *id, const char *path)
{
	FILE *f;
	int ret;
	mmfile_t cur = {NULL, 0};
	mmbuffer_t result = {NULL, 0};

	/*
	 * Normalize the conflicts in path and write it out to
	 * "thisimage" temporary file.
	 */
	if ((handle_file(istate, path, NULL, rerere_path(id, "thisimage")) < 0) ||
	    read_mmfile(&cur, rerere_path(id, "thisimage"))) {
		ret = 1;
		goto out;
	}

	ret = try_merge(istate, id, path, &cur, &result);
	if (ret)
		goto out;

	/*
	 * A successful replay of recorded resolution.
	 * Mark that "postimage" was used to help gc.
	 */
	if (utime(rerere_path(id, "postimage"), NULL) < 0)
		warning_errno(_("failed utime() on '%s'"),
			      rerere_path(id, "postimage"));

	/* Update "path" with the resolution */
	f = fopen(path, "w");
	if (!f)
		return error_errno(_("could not open '%s'"), path);
	if (fwrite(result.ptr, result.size, 1, f) != 1)
		error_errno(_("could not write '%s'"), path);
	if (fclose(f))
		return error_errno(_("writing '%s' failed"), path);

out:
	free(cur.ptr);
	free(result.ptr);

	return ret;
}