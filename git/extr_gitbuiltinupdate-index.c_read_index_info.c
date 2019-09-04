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
struct strbuf {char* buf; } ;
struct object_id {int dummy; } ;
typedef  scalar_t__ (* strbuf_getline_fn ) (struct strbuf*,int /*<<< orphan*/ ) ;
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ add_cacheinfo (unsigned int,struct object_id*,char*,int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ get_oid_hex (char*,struct object_id*) ; 
 scalar_t__ remove_file_from_cache (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_getline_nul (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 unsigned long strtoul (char*,char**,int) ; 
 TYPE_1__* the_hash_algo ; 
 scalar_t__ unquote_c_style (struct strbuf*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_path (char*,unsigned int) ; 

__attribute__((used)) static void read_index_info(int nul_term_line)
{
	const int hexsz = the_hash_algo->hexsz;
	struct strbuf buf = STRBUF_INIT;
	struct strbuf uq = STRBUF_INIT;
	strbuf_getline_fn getline_fn;

	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;
	while (getline_fn(&buf, stdin) != EOF) {
		char *ptr, *tab;
		char *path_name;
		struct object_id oid;
		unsigned int mode;
		unsigned long ul;
		int stage;

		/* This reads lines formatted in one of three formats:
		 *
		 * (1) mode         SP sha1          TAB path
		 * The first format is what "git apply --index-info"
		 * reports, and used to reconstruct a partial tree
		 * that is used for phony merge base tree when falling
		 * back on 3-way merge.
		 *
		 * (2) mode SP type SP sha1          TAB path
		 * The second format is to stuff "git ls-tree" output
		 * into the index file.
		 *
		 * (3) mode         SP sha1 SP stage TAB path
		 * This format is to put higher order stages into the
		 * index file and matches "git ls-files --stage" output.
		 */
		errno = 0;
		ul = strtoul(buf.buf, &ptr, 8);
		if (ptr == buf.buf || *ptr != ' '
		    || errno || (unsigned int) ul != ul)
			goto bad_line;
		mode = ul;

		tab = strchr(ptr, '\t');
		if (!tab || tab - ptr < hexsz + 1)
			goto bad_line;

		if (tab[-2] == ' ' && '0' <= tab[-1] && tab[-1] <= '3') {
			stage = tab[-1] - '0';
			ptr = tab + 1; /* point at the head of path */
			tab = tab - 2; /* point at tail of sha1 */
		}
		else {
			stage = 0;
			ptr = tab + 1; /* point at the head of path */
		}

		if (get_oid_hex(tab - hexsz, &oid) ||
			tab[-(hexsz + 1)] != ' ')
			goto bad_line;

		path_name = ptr;
		if (!nul_term_line && path_name[0] == '"') {
			strbuf_reset(&uq);
			if (unquote_c_style(&uq, path_name, NULL)) {
				die("git update-index: bad quoting of path name");
			}
			path_name = uq.buf;
		}

		if (!verify_path(path_name, mode)) {
			fprintf(stderr, "Ignoring path %s\n", path_name);
			continue;
		}

		if (!mode) {
			/* mode == 0 means there is no such path -- remove */
			if (remove_file_from_cache(path_name))
				die("git update-index: unable to remove %s",
				    ptr);
		}
		else {
			/* mode ' ' sha1 '\t' name
			 * ptr[-1] points at tab,
			 * ptr[-41] is at the beginning of sha1
			 */
			ptr[-(hexsz + 2)] = ptr[-1] = 0;
			if (add_cacheinfo(mode, &oid, path_name, stage))
				die("git update-index: unable to update %s",
				    path_name);
		}
		continue;

	bad_line:
		die("malformed index info %s", buf.buf);
	}
	strbuf_release(&buf);
	strbuf_release(&uq);
}