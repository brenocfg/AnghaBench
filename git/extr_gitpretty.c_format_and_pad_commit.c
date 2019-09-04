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
struct strbuf {char* buf; int len; } ;
struct format_commit_context {int padding; scalar_t__ flush_type; int truncate; TYPE_1__* pretty_ctx; } ;
struct TYPE_2__ {scalar_t__ graph_width; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int display_mode_esc_sequence_len (char const*) ; 
 scalar_t__ flush_both ; 
 scalar_t__ flush_left ; 
 scalar_t__ flush_left_and_steal ; 
 int format_commit_one (struct strbuf*,char const*,struct format_commit_context*) ; 
 int /*<<< orphan*/  memcpy (char const*,char const*,int) ; 
 scalar_t__ no_flush ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,char,int) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_utf8_replace (struct strbuf*,int,int,char*) ; 
 char* strrchr (char*,char) ; 
#define  trunc_left 131 
#define  trunc_middle 130 
#define  trunc_none 129 
#define  trunc_right 128 
 int utf8_strnwidth (char const*,int,int) ; 

__attribute__((used)) static size_t format_and_pad_commit(struct strbuf *sb, /* in UTF-8 */
				    const char *placeholder,
				    struct format_commit_context *c)
{
	struct strbuf local_sb = STRBUF_INIT;
	int total_consumed = 0, len, padding = c->padding;
	if (padding < 0) {
		const char *start = strrchr(sb->buf, '\n');
		int occupied;
		if (!start)
			start = sb->buf;
		occupied = utf8_strnwidth(start, -1, 1);
		occupied += c->pretty_ctx->graph_width;
		padding = (-padding) - occupied;
	}
	while (1) {
		int modifier = *placeholder == 'C';
		int consumed = format_commit_one(&local_sb, placeholder, c);
		total_consumed += consumed;

		if (!modifier)
			break;

		placeholder += consumed;
		if (*placeholder != '%')
			break;
		placeholder++;
		total_consumed++;
	}
	len = utf8_strnwidth(local_sb.buf, -1, 1);

	if (c->flush_type == flush_left_and_steal) {
		const char *ch = sb->buf + sb->len - 1;
		while (len > padding && ch > sb->buf) {
			const char *p;
			if (*ch == ' ') {
				ch--;
				padding++;
				continue;
			}
			/* check for trailing ansi sequences */
			if (*ch != 'm')
				break;
			p = ch - 1;
			while (ch - p < 10 && *p != '\033')
				p--;
			if (*p != '\033' ||
			    ch + 1 - p != display_mode_esc_sequence_len(p))
				break;
			/*
			 * got a good ansi sequence, put it back to
			 * local_sb as we're cutting sb
			 */
			strbuf_insert(&local_sb, 0, p, ch + 1 - p);
			ch = p - 1;
		}
		strbuf_setlen(sb, ch + 1 - sb->buf);
		c->flush_type = flush_left;
	}

	if (len > padding) {
		switch (c->truncate) {
		case trunc_left:
			strbuf_utf8_replace(&local_sb,
					    0, len - (padding - 2),
					    "..");
			break;
		case trunc_middle:
			strbuf_utf8_replace(&local_sb,
					    padding / 2 - 1,
					    len - (padding - 2),
					    "..");
			break;
		case trunc_right:
			strbuf_utf8_replace(&local_sb,
					    padding - 2, len - (padding - 2),
					    "..");
			break;
		case trunc_none:
			break;
		}
		strbuf_addbuf(sb, &local_sb);
	} else {
		int sb_len = sb->len, offset = 0;
		if (c->flush_type == flush_left)
			offset = padding - len;
		else if (c->flush_type == flush_both)
			offset = (padding - len) / 2;
		/*
		 * we calculate padding in columns, now
		 * convert it back to chars
		 */
		padding = padding - len + local_sb.len;
		strbuf_addchars(sb, ' ', padding);
		memcpy(sb->buf + sb_len + offset, local_sb.buf,
		       local_sb.len);
	}
	strbuf_release(&local_sb);
	c->flush_type = no_flush;
	return total_consumed;
}