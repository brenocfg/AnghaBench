#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {scalar_t__ seconds; } ;
struct TYPE_6__ {scalar_t__ seconds; } ;
struct TYPE_8__ {char* path; int mode; TYPE_2__ mtime; TYPE_1__ ctime; scalar_t__ gid; scalar_t__ uid; scalar_t__ ino; scalar_t__ dev; scalar_t__ file_size; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ *) ; 
 int git_index_entry_stage (TYPE_3__ const*) ; 
 size_t git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_3__* git_index_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_index_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_index_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open_ext (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 

int lg2_show_index(git_repository *repo, int argc, char** argv)
{
	git_index *index;
	size_t i, ecount;
	char *dir = ".";
	size_t dirlen;
	char out[GIT_OID_HEXSZ+1];
	out[GIT_OID_HEXSZ] = '\0';

	if (argc > 2)
		fatal("usage: showindex [<repo-dir>]", NULL);
	if (argc > 1)
		dir = argv[1];

	dirlen = strlen(dir);
	if (dirlen > 5 && strcmp(dir + dirlen - 5, "index") == 0) {
		check_lg2(git_index_open(&index, dir), "could not open index", dir);
	} else {
		check_lg2(git_repository_open_ext(&repo, dir, 0, NULL), "could not open repository", dir);
		check_lg2(git_repository_index(&index, repo), "could not open repository index", NULL);
		git_repository_free(repo);
	}

	git_index_read(index, 0);

	ecount = git_index_entrycount(index);
	if (!ecount)
		printf("Empty index\n");

	for (i = 0; i < ecount; ++i) {
		const git_index_entry *e = git_index_get_byindex(index, i);

		git_oid_fmt(out, &e->id);

		printf("File Path: %s\n", e->path);
		printf("    Stage: %d\n", git_index_entry_stage(e));
		printf(" Blob SHA: %s\n", out);
		printf("File Mode: %07o\n", e->mode);
		printf("File Size: %d bytes\n", (int)e->file_size);
		printf("Dev/Inode: %d/%d\n", (int)e->dev, (int)e->ino);
		printf("  UID/GID: %d/%d\n", (int)e->uid, (int)e->gid);
		printf("    ctime: %d\n", (int)e->ctime.seconds);
		printf("    mtime: %d\n", (int)e->mtime.seconds);
		printf("\n");
	}

	git_index_free(index);

	return 0;
}