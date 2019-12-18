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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct diff_options {int dummy; } ;
struct diff_filespec {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SYMBOL_SUMMARY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_c_style (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void show_file_mode_name(struct diff_options *opt, const char *newdelete, struct diff_filespec *fs)
{
	struct strbuf sb = STRBUF_INIT;
	if (fs->mode)
		strbuf_addf(&sb, " %s mode %06o ", newdelete, fs->mode);
	else
		strbuf_addf(&sb, " %s ", newdelete);

	quote_c_style(fs->path, &sb, NULL, 0);
	strbuf_addch(&sb, '\n');
	emit_diff_symbol(opt, DIFF_SYMBOL_SUMMARY,
			 sb.buf, sb.len, 0);
	strbuf_release(&sb);
}