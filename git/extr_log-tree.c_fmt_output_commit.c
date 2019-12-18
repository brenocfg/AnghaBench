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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct rev_info {int dummy; } ;
struct pretty_print_context {int /*<<< orphan*/  member_0; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fmt_output_subject (struct strbuf*,int /*<<< orphan*/ ,struct rev_info*) ; 
 int /*<<< orphan*/  format_commit_message (struct commit*,char*,struct strbuf*,struct pretty_print_context*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void fmt_output_commit(struct strbuf *filename,
		       struct commit *commit,
		       struct rev_info *info)
{
	struct pretty_print_context ctx = {0};
	struct strbuf subject = STRBUF_INIT;

	format_commit_message(commit, "%f", &subject, &ctx);
	fmt_output_subject(filename, subject.buf, info);
	strbuf_release(&subject);
}