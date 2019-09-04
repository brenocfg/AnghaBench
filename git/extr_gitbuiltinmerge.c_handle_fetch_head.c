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
struct strbuf {int len; char* buf; } ;
struct object_id {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_4__ {struct commit_list* next; } ;
struct TYPE_3__ {unsigned int hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ close (int) ; 
 TYPE_2__* commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 struct commit* get_merge_parent (char*) ; 
 scalar_t__ get_oid_hex (char*,struct object_id*) ; 
 char* git_path_fetch_head (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void handle_fetch_head(struct commit_list **remotes, struct strbuf *merge_names)
{
	const char *filename;
	int fd, pos, npos;
	struct strbuf fetch_head_file = STRBUF_INIT;
	const unsigned hexsz = the_hash_algo->hexsz;

	if (!merge_names)
		merge_names = &fetch_head_file;

	filename = git_path_fetch_head(the_repository);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		die_errno(_("could not open '%s' for reading"), filename);

	if (strbuf_read(merge_names, fd, 0) < 0)
		die_errno(_("could not read '%s'"), filename);
	if (close(fd) < 0)
		die_errno(_("could not close '%s'"), filename);

	for (pos = 0; pos < merge_names->len; pos = npos) {
		struct object_id oid;
		char *ptr;
		struct commit *commit;

		ptr = strchr(merge_names->buf + pos, '\n');
		if (ptr)
			npos = ptr - merge_names->buf + 1;
		else
			npos = merge_names->len;

		if (npos - pos < hexsz + 2 ||
		    get_oid_hex(merge_names->buf + pos, &oid))
			commit = NULL; /* bad */
		else if (memcmp(merge_names->buf + pos + hexsz, "\t\t", 2))
			continue; /* not-for-merge */
		else {
			char saved = merge_names->buf[pos + hexsz];
			merge_names->buf[pos + hexsz] = '\0';
			commit = get_merge_parent(merge_names->buf + pos);
			merge_names->buf[pos + hexsz] = saved;
		}
		if (!commit) {
			if (ptr)
				*ptr = '\0';
			die(_("not something we can merge in %s: %s"),
			    filename, merge_names->buf + pos);
		}
		remotes = &commit_list_insert(commit, remotes)->next;
	}

	if (merge_names == &fetch_head_file)
		strbuf_release(&fetch_head_file);
}