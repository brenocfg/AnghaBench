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
struct TYPE_4__ {scalar_t__ mode; int /*<<< orphan*/  path; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SYMBOL_SUMMARY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_c_style (int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void show_mode_change(struct diff_options *opt, struct diff_filepair *p,
		int show_name)
{
	if (p->one->mode && p->two->mode && p->one->mode != p->two->mode) {
		struct strbuf sb = STRBUF_INIT;
		strbuf_addf(&sb, " mode change %06o => %06o",
			    p->one->mode, p->two->mode);
		if (show_name) {
			strbuf_addch(&sb, ' ');
			quote_c_style(p->two->path, &sb, NULL, 0);
		}
		strbuf_addch(&sb, '\n');
		emit_diff_symbol(opt, DIFF_SYMBOL_SUMMARY,
				 sb.buf, sb.len, 0);
		strbuf_release(&sb);
	}
}