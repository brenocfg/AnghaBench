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
struct tm {int dummy; } ;
struct strbuf {char* buf; size_t len; scalar_t__ alloc; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 char* strchrnul (char const*,char) ; 
 size_t strftime (char*,scalar_t__,char const*,struct tm const*) ; 

void strbuf_addftime(struct strbuf *sb, const char *fmt, const struct tm *tm,
		     int tz_offset, int suppress_tz_name)
{
	struct strbuf munged_fmt = STRBUF_INIT;
	size_t hint = 128;
	size_t len;

	if (!*fmt)
		return;

	/*
	 * There is no portable way to pass timezone information to
	 * strftime, so we handle %z and %Z here.
	 */
	for (;;) {
		const char *percent = strchrnul(fmt, '%');
		strbuf_add(&munged_fmt, fmt, percent - fmt);
		if (!*percent)
			break;
		fmt = percent + 1;
		switch (*fmt) {
		case '%':
			strbuf_addstr(&munged_fmt, "%%");
			fmt++;
			break;
		case 'z':
			strbuf_addf(&munged_fmt, "%+05d", tz_offset);
			fmt++;
			break;
		case 'Z':
			if (suppress_tz_name) {
				fmt++;
				break;
			}
			/* FALLTHROUGH */
		default:
			strbuf_addch(&munged_fmt, '%');
		}
	}
	fmt = munged_fmt.buf;

	strbuf_grow(sb, hint);
	len = strftime(sb->buf + sb->len, sb->alloc - sb->len, fmt, tm);

	if (!len) {
		/*
		 * strftime reports "0" if it could not fit the result in the buffer.
		 * Unfortunately, it also reports "0" if the requested time string
		 * takes 0 bytes. So our strategy is to munge the format so that the
		 * output contains at least one character, and then drop the extra
		 * character before returning.
		 */
		strbuf_addch(&munged_fmt, ' ');
		while (!len) {
			hint *= 2;
			strbuf_grow(sb, hint);
			len = strftime(sb->buf + sb->len, sb->alloc - sb->len,
				       munged_fmt.buf, tm);
		}
		len--; /* drop munged space */
	}
	strbuf_release(&munged_fmt);
	strbuf_setlen(sb, sb->len + len);
}