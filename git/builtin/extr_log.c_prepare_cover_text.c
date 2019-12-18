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
struct strbuf {scalar_t__ len; char* buf; } ;
struct pretty_print_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ COVER_FROM_AUTO ; 
 scalar_t__ COVER_FROM_AUTO_MAX_SUBJECT_LEN ; 
 scalar_t__ COVER_FROM_MESSAGE ; 
 scalar_t__ COVER_FROM_NONE ; 
 scalar_t__ COVER_FROM_SUBJECT ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ cover_from_description_mode ; 
 char* format_subject (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  pp_remainder (struct pretty_print_context*,char const**,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_title_line (struct pretty_print_context*,char const**,struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  read_branch_desc (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void prepare_cover_text(struct pretty_print_context *pp,
			       const char *branch_name,
			       struct strbuf *sb,
			       const char *encoding,
			       int need_8bit_cte)
{
	const char *subject = "*** SUBJECT HERE ***";
	const char *body = "*** BLURB HERE ***";
	struct strbuf description_sb = STRBUF_INIT;
	struct strbuf subject_sb = STRBUF_INIT;

	if (cover_from_description_mode == COVER_FROM_NONE)
		goto do_pp;

	if (branch_name && *branch_name)
		read_branch_desc(&description_sb, branch_name);
	if (!description_sb.len)
		goto do_pp;

	if (cover_from_description_mode == COVER_FROM_SUBJECT ||
			cover_from_description_mode == COVER_FROM_AUTO)
		body = format_subject(&subject_sb, description_sb.buf, " ");

	if (cover_from_description_mode == COVER_FROM_MESSAGE ||
			(cover_from_description_mode == COVER_FROM_AUTO &&
			 subject_sb.len > COVER_FROM_AUTO_MAX_SUBJECT_LEN))
		body = description_sb.buf;
	else
		subject = subject_sb.buf;

do_pp:
	pp_title_line(pp, &subject, sb, encoding, need_8bit_cte);
	pp_remainder(pp, &body, sb, 0);

	strbuf_release(&description_sb);
	strbuf_release(&subject_sb);
}