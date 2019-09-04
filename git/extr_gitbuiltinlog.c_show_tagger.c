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
struct TYPE_2__ {int /*<<< orphan*/  file; } ;
struct rev_info {TYPE_1__ diffopt; int /*<<< orphan*/  date_mode; int /*<<< orphan*/  commit_format; } ;
struct pretty_print_context {int /*<<< orphan*/  date_mode; int /*<<< orphan*/  fmt; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  get_log_output_encoding () ; 
 int /*<<< orphan*/  pp_user_info (struct pretty_print_context*,char*,struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void show_tagger(const char *buf, struct rev_info *rev)
{
	struct strbuf out = STRBUF_INIT;
	struct pretty_print_context pp = {0};

	pp.fmt = rev->commit_format;
	pp.date_mode = rev->date_mode;
	pp_user_info(&pp, "Tagger", &out, buf, get_log_output_encoding());
	fprintf(rev->diffopt.file, "%s", out.buf);
	strbuf_release(&out);
}