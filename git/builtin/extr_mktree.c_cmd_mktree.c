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
struct strbuf {char* buf; } ;
struct option {int dummy; } ;
struct object_id {int dummy; } ;
typedef  scalar_t__ (* strbuf_getline_fn ) (struct strbuf*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option const OPT_BOOL (char,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 struct option const OPT_END () ; 
 struct option const OPT_SET_INT (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ,int) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mktree_line (char*,int,int) ; 
 int /*<<< orphan*/  mktree_usage ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int parse_options (int,char const**,char const*,struct option const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_getline_nul (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int used ; 
 int /*<<< orphan*/  write_tree (struct object_id*) ; 

int cmd_mktree(int ac, const char **av, const char *prefix)
{
	struct strbuf sb = STRBUF_INIT;
	struct object_id oid;
	int nul_term_line = 0;
	int allow_missing = 0;
	int is_batch_mode = 0;
	int got_eof = 0;
	strbuf_getline_fn getline_fn;

	const struct option option[] = {
		OPT_BOOL('z', NULL, &nul_term_line, N_("input is NUL terminated")),
		OPT_SET_INT( 0 , "missing", &allow_missing, N_("allow missing objects"), 1),
		OPT_SET_INT( 0 , "batch", &is_batch_mode, N_("allow creation of more than one tree"), 1),
		OPT_END()
	};

	ac = parse_options(ac, av, prefix, option, mktree_usage, 0);
	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;

	while (!got_eof) {
		while (1) {
			if (getline_fn(&sb, stdin) == EOF) {
				got_eof = 1;
				break;
			}
			if (sb.buf[0] == '\0') {
				/* empty lines denote tree boundaries in batch mode */
				if (is_batch_mode)
					break;
				die("input format error: (blank line only valid in batch mode)");
			}
			mktree_line(sb.buf, nul_term_line, allow_missing);
		}
		if (is_batch_mode && got_eof && used < 1) {
			/*
			 * Execution gets here if the last tree entry is terminated with a
			 * new-line.  The final new-line has been made optional to be
			 * consistent with the original non-batch behaviour of mktree.
			 */
			; /* skip creating an empty tree */
		} else {
			write_tree(&oid);
			puts(oid_to_hex(&oid));
			fflush(stdout);
		}
		used=0; /* reset tree entry buffer for re-use in batch mode */
	}
	strbuf_release(&sb);
	exit(0);
}