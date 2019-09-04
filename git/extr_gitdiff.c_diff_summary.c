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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct diff_options {int dummy; } ;
struct diff_filepair {int status; int /*<<< orphan*/  score; TYPE_1__* two; TYPE_1__* one; } ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
#define  DIFF_STATUS_ADDED 131 
#define  DIFF_STATUS_COPIED 130 
#define  DIFF_STATUS_DELETED 129 
#define  DIFF_STATUS_RENAMED 128 
 int /*<<< orphan*/  DIFF_SYMBOL_SUMMARY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_c_style (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_file_mode_name (struct diff_options*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  show_mode_change (struct diff_options*,struct diff_filepair*,int) ; 
 int /*<<< orphan*/  show_rename_copy (struct diff_options*,char*,struct diff_filepair*) ; 
 int /*<<< orphan*/  similarity_index (struct diff_filepair*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void diff_summary(struct diff_options *opt, struct diff_filepair *p)
{
	switch(p->status) {
	case DIFF_STATUS_DELETED:
		show_file_mode_name(opt, "delete", p->one);
		break;
	case DIFF_STATUS_ADDED:
		show_file_mode_name(opt, "create", p->two);
		break;
	case DIFF_STATUS_COPIED:
		show_rename_copy(opt, "copy", p);
		break;
	case DIFF_STATUS_RENAMED:
		show_rename_copy(opt, "rename", p);
		break;
	default:
		if (p->score) {
			struct strbuf sb = STRBUF_INIT;
			strbuf_addstr(&sb, " rewrite ");
			quote_c_style(p->two->path, &sb, NULL, 0);
			strbuf_addf(&sb, " (%d%%)\n", similarity_index(p));
			emit_diff_symbol(opt, DIFF_SYMBOL_SUMMARY,
					 sb.buf, sb.len, 0);
			strbuf_release(&sb);
		}
		show_mode_change(opt, p, !p->score);
		break;
	}
}