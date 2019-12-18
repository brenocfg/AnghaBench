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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct diff_options {int dummy; } ;
struct diff_filepair {TYPE_2__* two; TYPE_1__* one; } ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SYMBOL_SUMMARY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pprint_rename (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_mode_change (struct diff_options*,struct diff_filepair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  similarity_index (struct diff_filepair*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void show_rename_copy(struct diff_options *opt, const char *renamecopy,
		struct diff_filepair *p)
{
	struct strbuf sb = STRBUF_INIT;
	struct strbuf names = STRBUF_INIT;

	pprint_rename(&names, p->one->path, p->two->path);
	strbuf_addf(&sb, " %s %s (%d%%)\n",
		    renamecopy, names.buf, similarity_index(p));
	strbuf_release(&names);
	emit_diff_symbol(opt, DIFF_SYMBOL_SUMMARY,
				 sb.buf, sb.len, 0);
	show_mode_change(opt, p, 0);
	strbuf_release(&sb);
}