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
struct strbuf {unsigned long len; } ;
struct pretty_print_context {int need_8bit_cte; scalar_t__ fmt; int /*<<< orphan*/  print_email_subject; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ CMIT_FMT_ONELINE ; 
 scalar_t__ CMIT_FMT_USERFORMAT ; 
 scalar_t__ cmit_fmt_is_mail (scalar_t__) ; 
 int /*<<< orphan*/  format_commit_message (struct commit const*,int /*<<< orphan*/ ,struct strbuf*,struct pretty_print_context*) ; 
 char* get_log_output_encoding () ; 
 char* logmsg_reencode (struct commit const*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ non_ascii (int) ; 
 int /*<<< orphan*/  pp_header (struct pretty_print_context*,char const*,struct commit const*,char const**,struct strbuf*) ; 
 int /*<<< orphan*/  pp_remainder (struct pretty_print_context*,char const**,struct strbuf*,int) ; 
 int /*<<< orphan*/  pp_title_line (struct pretty_print_context*,char const**,struct strbuf*,char const*,int) ; 
 char* skip_blank_lines (char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit const*,char const*) ; 
 int /*<<< orphan*/  user_format ; 

void pretty_print_commit(struct pretty_print_context *pp,
			 const struct commit *commit,
			 struct strbuf *sb)
{
	unsigned long beginning_of_body;
	int indent = 4;
	const char *msg;
	const char *reencoded;
	const char *encoding;
	int need_8bit_cte = pp->need_8bit_cte;

	if (pp->fmt == CMIT_FMT_USERFORMAT) {
		format_commit_message(commit, user_format, sb, pp);
		return;
	}

	encoding = get_log_output_encoding();
	msg = reencoded = logmsg_reencode(commit, NULL, encoding);

	if (pp->fmt == CMIT_FMT_ONELINE || cmit_fmt_is_mail(pp->fmt))
		indent = 0;

	/*
	 * We need to check and emit Content-type: to mark it
	 * as 8-bit if we haven't done so.
	 */
	if (cmit_fmt_is_mail(pp->fmt) && need_8bit_cte == 0) {
		int i, ch, in_body;

		for (in_body = i = 0; (ch = msg[i]); i++) {
			if (!in_body) {
				/* author could be non 7-bit ASCII but
				 * the log may be so; skip over the
				 * header part first.
				 */
				if (ch == '\n' && msg[i+1] == '\n')
					in_body = 1;
			}
			else if (non_ascii(ch)) {
				need_8bit_cte = 1;
				break;
			}
		}
	}

	pp_header(pp, encoding, commit, &msg, sb);
	if (pp->fmt != CMIT_FMT_ONELINE && !pp->print_email_subject) {
		strbuf_addch(sb, '\n');
	}

	/* Skip excess blank lines at the beginning of body, if any... */
	msg = skip_blank_lines(msg);

	/* These formats treat the title line specially. */
	if (pp->fmt == CMIT_FMT_ONELINE || cmit_fmt_is_mail(pp->fmt))
		pp_title_line(pp, &msg, sb, encoding, need_8bit_cte);

	beginning_of_body = sb->len;
	if (pp->fmt != CMIT_FMT_ONELINE)
		pp_remainder(pp, &msg, sb, indent);
	strbuf_rtrim(sb);

	/* Make sure there is an EOLN for the non-oneline case */
	if (pp->fmt != CMIT_FMT_ONELINE)
		strbuf_addch(sb, '\n');

	/*
	 * The caller may append additional body text in e-mail
	 * format.  Make sure we did not strip the blank line
	 * between the header and the body.
	 */
	if (cmit_fmt_is_mail(pp->fmt) && sb->len <= beginning_of_body)
		strbuf_addch(sb, '\n');

	unuse_commit_buffer(commit, reencoded);
}