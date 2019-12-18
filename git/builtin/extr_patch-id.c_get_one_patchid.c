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
typedef  int /*<<< orphan*/  git_hash_ctx ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,char*,int) ;int /*<<< orphan*/  (* init_fn ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  flush_one_hunk (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_oid_hex (char const*,struct object_id*) ; 
 int /*<<< orphan*/  isalpha (char) ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 int remove_space (char*) ; 
 int /*<<< orphan*/  scan_hunk_header (char*,int*,int*) ; 
 int /*<<< orphan*/  skip_prefix (char*,char*,char const**) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ ,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static int get_one_patchid(struct object_id *next_oid, struct object_id *result,
			   struct strbuf *line_buf, int stable)
{
	int patchlen = 0, found_next = 0;
	int before = -1, after = -1;
	git_hash_ctx ctx;

	the_hash_algo->init_fn(&ctx);
	oidclr(result);

	while (strbuf_getwholeline(line_buf, stdin, '\n') != EOF) {
		char *line = line_buf->buf;
		const char *p = line;
		int len;

		if (!skip_prefix(line, "diff-tree ", &p) &&
		    !skip_prefix(line, "commit ", &p) &&
		    !skip_prefix(line, "From ", &p) &&
		    starts_with(line, "\\ ") && 12 < strlen(line))
			continue;

		if (!get_oid_hex(p, next_oid)) {
			found_next = 1;
			break;
		}

		/* Ignore commit comments */
		if (!patchlen && !starts_with(line, "diff "))
			continue;

		/* Parsing diff header?  */
		if (before == -1) {
			if (starts_with(line, "index "))
				continue;
			else if (starts_with(line, "--- "))
				before = after = 1;
			else if (!isalpha(line[0]))
				break;
		}

		/* Looking for a valid hunk header?  */
		if (before == 0 && after == 0) {
			if (starts_with(line, "@@ -")) {
				/* Parse next hunk, but ignore line numbers.  */
				scan_hunk_header(line, &before, &after);
				continue;
			}

			/* Split at the end of the patch.  */
			if (!starts_with(line, "diff "))
				break;

			/* Else we're parsing another header.  */
			if (stable)
				flush_one_hunk(result, &ctx);
			before = after = -1;
		}

		/* If we get here, we're inside a hunk.  */
		if (line[0] == '-' || line[0] == ' ')
			before--;
		if (line[0] == '+' || line[0] == ' ')
			after--;

		/* Compute the sha without whitespace */
		len = remove_space(line);
		patchlen += len;
		the_hash_algo->update_fn(&ctx, line, len);
	}

	if (!found_next)
		oidclr(next_oid);

	flush_one_hunk(result, &ctx);

	return patchlen;
}