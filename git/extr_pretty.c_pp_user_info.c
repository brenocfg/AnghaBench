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
struct strbuf {char const* buf; size_t len; } ;
struct pretty_print_context {int fmt; int /*<<< orphan*/  date_mode; TYPE_1__* from_ident; int /*<<< orphan*/  in_body_headers; scalar_t__ mailmap; } ;
struct ident_split {char* mail_begin; char* mail_end; char* name_begin; char* name_end; } ;
struct TYPE_2__ {char* mail_begin; char const* mail_end; char* name_begin; char const* name_end; } ;

/* Variables and functions */
#define  CMIT_FMT_EMAIL 131 
#define  CMIT_FMT_FULLER 130 
#define  CMIT_FMT_MBOXRD 129 
#define  CMIT_FMT_MEDIUM 128 
 int CMIT_FMT_ONELINE ; 
 int /*<<< orphan*/ * DATE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFC2047_ADDRESS ; 
 int /*<<< orphan*/  RFC2822 ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_rfc2047 (struct strbuf*,char const*,size_t,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_rfc822_quoted (struct strbuf*,char const*,size_t) ; 
 scalar_t__ cmit_fmt_is_mail (int) ; 
 scalar_t__ ident_cmp (TYPE_1__*,struct ident_split*) ; 
 size_t last_line_length (struct strbuf*) ; 
 int /*<<< orphan*/  map_user (scalar_t__,char const**,size_t*,char const**,size_t*) ; 
 scalar_t__ needs_rfc2047_encoding (char const*,size_t) ; 
 scalar_t__ needs_rfc822_quoting (char const*,size_t) ; 
 int /*<<< orphan*/  show_ident_date (struct ident_split*,int /*<<< orphan*/ *) ; 
 scalar_t__ split_ident_line (struct ident_split*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_add_wrapped_bytes (struct strbuf*,char const*,size_t,int,int,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchrnul (char const*,char) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

void pp_user_info(struct pretty_print_context *pp,
		  const char *what, struct strbuf *sb,
		  const char *line, const char *encoding)
{
	struct ident_split ident;
	char *line_end;
	const char *mailbuf, *namebuf;
	size_t namelen, maillen;
	int max_length = 78; /* per rfc2822 */

	if (pp->fmt == CMIT_FMT_ONELINE)
		return;

	line_end = strchrnul(line, '\n');
	if (split_ident_line(&ident, line, line_end - line))
		return;

	mailbuf = ident.mail_begin;
	maillen = ident.mail_end - ident.mail_begin;
	namebuf = ident.name_begin;
	namelen = ident.name_end - ident.name_begin;

	if (pp->mailmap)
		map_user(pp->mailmap, &mailbuf, &maillen, &namebuf, &namelen);

	if (cmit_fmt_is_mail(pp->fmt)) {
		if (pp->from_ident && ident_cmp(pp->from_ident, &ident)) {
			struct strbuf buf = STRBUF_INIT;

			strbuf_addstr(&buf, "From: ");
			strbuf_add(&buf, namebuf, namelen);
			strbuf_addstr(&buf, " <");
			strbuf_add(&buf, mailbuf, maillen);
			strbuf_addstr(&buf, ">\n");
			string_list_append(&pp->in_body_headers,
					   strbuf_detach(&buf, NULL));

			mailbuf = pp->from_ident->mail_begin;
			maillen = pp->from_ident->mail_end - mailbuf;
			namebuf = pp->from_ident->name_begin;
			namelen = pp->from_ident->name_end - namebuf;
		}

		strbuf_addstr(sb, "From: ");
		if (needs_rfc2047_encoding(namebuf, namelen)) {
			add_rfc2047(sb, namebuf, namelen,
				    encoding, RFC2047_ADDRESS);
			max_length = 76; /* per rfc2047 */
		} else if (needs_rfc822_quoting(namebuf, namelen)) {
			struct strbuf quoted = STRBUF_INIT;
			add_rfc822_quoted(&quoted, namebuf, namelen);
			strbuf_add_wrapped_bytes(sb, quoted.buf, quoted.len,
							-6, 1, max_length);
			strbuf_release(&quoted);
		} else {
			strbuf_add_wrapped_bytes(sb, namebuf, namelen,
						 -6, 1, max_length);
		}

		if (max_length <
		    last_line_length(sb) + strlen(" <") + maillen + strlen(">"))
			strbuf_addch(sb, '\n');
		strbuf_addf(sb, " <%.*s>\n", (int)maillen, mailbuf);
	} else {
		strbuf_addf(sb, "%s: %.*s%.*s <%.*s>\n", what,
			    (pp->fmt == CMIT_FMT_FULLER) ? 4 : 0, "    ",
			    (int)namelen, namebuf, (int)maillen, mailbuf);
	}

	switch (pp->fmt) {
	case CMIT_FMT_MEDIUM:
		strbuf_addf(sb, "Date:   %s\n",
			    show_ident_date(&ident, &pp->date_mode));
		break;
	case CMIT_FMT_EMAIL:
	case CMIT_FMT_MBOXRD:
		strbuf_addf(sb, "Date: %s\n",
			    show_ident_date(&ident, DATE_MODE(RFC2822)));
		break;
	case CMIT_FMT_FULLER:
		strbuf_addf(sb, "%sDate: %s\n", what,
			    show_ident_date(&ident, &pp->date_mode));
		break;
	default:
		/* notin' */
		break;
	}
}