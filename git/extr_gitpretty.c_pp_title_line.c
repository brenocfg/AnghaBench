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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int nr; TYPE_1__* items; } ;
struct pretty_print_context {TYPE_2__ in_body_headers; int /*<<< orphan*/  fmt; scalar_t__ after_subject; scalar_t__ rev; scalar_t__ print_email_subject; scalar_t__ preserve_subject; } ;
struct TYPE_3__ {scalar_t__ string; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFC2047_SUBJECT ; 
 int /*<<< orphan*/  add_rfc2047 (struct strbuf*,int /*<<< orphan*/ ,scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ cmit_fmt_is_mail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmt_output_email_subject (struct strbuf*,scalar_t__) ; 
 char* format_subject (struct strbuf*,char const*,char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ has_non_ascii (scalar_t__) ; 
 int /*<<< orphan*/  last_line_length (struct strbuf*) ; 
 scalar_t__ needs_rfc2047_encoding (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_add_wrapped_bytes (struct strbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int const) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_clear (TYPE_2__*,int /*<<< orphan*/ ) ; 

void pp_title_line(struct pretty_print_context *pp,
		   const char **msg_p,
		   struct strbuf *sb,
		   const char *encoding,
		   int need_8bit_cte)
{
	static const int max_length = 78; /* per rfc2047 */
	struct strbuf title;

	strbuf_init(&title, 80);
	*msg_p = format_subject(&title, *msg_p,
				pp->preserve_subject ? "\n" : " ");

	strbuf_grow(sb, title.len + 1024);
	if (pp->print_email_subject) {
		if (pp->rev)
			fmt_output_email_subject(sb, pp->rev);
		if (needs_rfc2047_encoding(title.buf, title.len))
			add_rfc2047(sb, title.buf, title.len,
						encoding, RFC2047_SUBJECT);
		else
			strbuf_add_wrapped_bytes(sb, title.buf, title.len,
					 -last_line_length(sb), 1, max_length);
	} else {
		strbuf_addbuf(sb, &title);
	}
	strbuf_addch(sb, '\n');

	if (need_8bit_cte == 0) {
		int i;
		for (i = 0; i < pp->in_body_headers.nr; i++) {
			if (has_non_ascii(pp->in_body_headers.items[i].string)) {
				need_8bit_cte = 1;
				break;
			}
		}
	}

	if (need_8bit_cte > 0) {
		const char *header_fmt =
			"MIME-Version: 1.0\n"
			"Content-Type: text/plain; charset=%s\n"
			"Content-Transfer-Encoding: 8bit\n";
		strbuf_addf(sb, header_fmt, encoding);
	}
	if (pp->after_subject) {
		strbuf_addstr(sb, pp->after_subject);
	}
	if (cmit_fmt_is_mail(pp->fmt)) {
		strbuf_addch(sb, '\n');
	}

	if (pp->in_body_headers.nr) {
		int i;
		for (i = 0; i < pp->in_body_headers.nr; i++) {
			strbuf_addstr(sb, pp->in_body_headers.items[i].string);
			free(pp->in_body_headers.items[i].string);
		}
		string_list_clear(&pp->in_body_headers, 0);
		strbuf_addch(sb, '\n');
	}

	strbuf_release(&title);
}