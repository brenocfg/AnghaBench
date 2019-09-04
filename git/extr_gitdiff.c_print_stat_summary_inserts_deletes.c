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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; } ;
struct diff_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SYMBOL_STATS_SUMMARY_INSERTS_DELETES ; 
 int /*<<< orphan*/  DIFF_SYMBOL_STATS_SUMMARY_NO_FILES ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void print_stat_summary_inserts_deletes(struct diff_options *options,
		int files, int insertions, int deletions)
{
	struct strbuf sb = STRBUF_INIT;

	if (!files) {
		assert(insertions == 0 && deletions == 0);
		emit_diff_symbol(options, DIFF_SYMBOL_STATS_SUMMARY_NO_FILES,
				 NULL, 0, 0);
		return;
	}

	strbuf_addf(&sb,
		    (files == 1) ? " %d file changed" : " %d files changed",
		    files);

	/*
	 * For binary diff, the caller may want to print "x files
	 * changed" with insertions == 0 && deletions == 0.
	 *
	 * Not omitting "0 insertions(+), 0 deletions(-)" in this case
	 * is probably less confusing (i.e skip over "2 files changed
	 * but nothing about added/removed lines? Is this a bug in Git?").
	 */
	if (insertions || deletions == 0) {
		strbuf_addf(&sb,
			    (insertions == 1) ? ", %d insertion(+)" : ", %d insertions(+)",
			    insertions);
	}

	if (deletions || insertions == 0) {
		strbuf_addf(&sb,
			    (deletions == 1) ? ", %d deletion(-)" : ", %d deletions(-)",
			    deletions);
	}
	strbuf_addch(&sb, '\n');
	emit_diff_symbol(options, DIFF_SYMBOL_STATS_SUMMARY_INSERTS_DELETES,
			 sb.buf, sb.len, 0);
	strbuf_release(&sb);
}