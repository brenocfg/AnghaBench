#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct packref {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  peel; int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  peel ;
typedef  int /*<<< orphan*/  oid ;
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int PACKREF_HAS_PEEL ; 
 scalar_t__ git_filebuf_printf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  git_oid_nfmt (char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int packed_write_ref(struct packref *ref, git_filebuf *file)
{
	char oid[GIT_OID_HEXSZ + 1];
	git_oid_nfmt(oid, sizeof(oid), &ref->oid);

	/*
	 * For references that peel to an object in the repo, we must
	 * write the resulting peel on a separate line, e.g.
	 *
	 *	6fa8a902cc1d18527e1355773c86721945475d37 refs/tags/libgit2-0.4
	 *	^2ec0cb7959b0bf965d54f95453f5b4b34e8d3100
	 *
	 * This obviously only applies to tags.
	 * The required peels have already been loaded into `ref->peel_target`.
	 */
	if (ref->flags & PACKREF_HAS_PEEL) {
		char peel[GIT_OID_HEXSZ + 1];
		git_oid_nfmt(peel, sizeof(peel), &ref->peel);

		if (git_filebuf_printf(file, "%s %s\n^%s\n", oid, ref->name, peel) < 0)
			return -1;
	} else {
		if (git_filebuf_printf(file, "%s %s\n", oid, ref->name) < 0)
			return -1;
	}

	return 0;
}