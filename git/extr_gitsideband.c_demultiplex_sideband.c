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
struct strbuf {char* buf; scalar_t__ len; } ;
typedef  enum sideband_type { ____Placeholder_sideband_type } sideband_type ;

/* Variables and functions */
 char* ANSI_SUFFIX ; 
 char* DISPLAY_PREFIX ; 
 char* DUMB_SUFFIX ; 
 int SIDEBAND_FLUSH ; 
 int SIDEBAND_PRIMARY ; 
 int SIDEBAND_PROTOCOL_ERROR ; 
 int SIDEBAND_REMOTE_ERROR ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  is_terminal_dumb () ; 
 scalar_t__ isatty (int) ; 
 int /*<<< orphan*/  maybe_colorize_sideband (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char const) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int strlen (char const*) ; 
 char* strpbrk (char const*,char*) ; 
 int /*<<< orphan*/  xwrite (int,char*,scalar_t__) ; 

int demultiplex_sideband(const char *me, char *buf, int len,
			 int die_on_error,
			 struct strbuf *scratch,
			 enum sideband_type *sideband_type)
{
	static const char *suffix;
	const char *b, *brk;
	int band;

	if (!suffix) {
		if (isatty(2) && !is_terminal_dumb())
			suffix = ANSI_SUFFIX;
		else
			suffix = DUMB_SUFFIX;
	}

	if (len == 0) {
		*sideband_type = SIDEBAND_FLUSH;
		goto cleanup;
	}
	if (len < 1) {
		strbuf_addf(scratch,
			    "%s%s: protocol error: no band designator",
			    scratch->len ? "\n" : "", me);
		*sideband_type = SIDEBAND_PROTOCOL_ERROR;
		goto cleanup;
	}
	band = buf[0] & 0xff;
	buf[len] = '\0';
	len--;
	switch (band) {
	case 3:
		if (die_on_error)
			die("remote error: %s", buf + 1);
		strbuf_addf(scratch, "%s%s", scratch->len ? "\n" : "",
			    DISPLAY_PREFIX);
		maybe_colorize_sideband(scratch, buf + 1, len);

		*sideband_type = SIDEBAND_REMOTE_ERROR;
		break;
	case 2:
		b = buf + 1;

		/*
		 * Append a suffix to each nonempty line to clear the
		 * end of the screen line.
		 *
		 * The output is accumulated in a buffer and
		 * each line is printed to stderr using
		 * write(2) to ensure inter-process atomicity.
		 */
		while ((brk = strpbrk(b, "\n\r"))) {
			int linelen = brk - b;

			if (!scratch->len)
				strbuf_addstr(scratch, DISPLAY_PREFIX);
			if (linelen > 0) {
				maybe_colorize_sideband(scratch, b, linelen);
				strbuf_addstr(scratch, suffix);
			}

			strbuf_addch(scratch, *brk);
			xwrite(2, scratch->buf, scratch->len);
			strbuf_reset(scratch);

			b = brk + 1;
		}

		if (*b) {
			strbuf_addstr(scratch, scratch->len ?
				    "" : DISPLAY_PREFIX);
			maybe_colorize_sideband(scratch, b, strlen(b));
		}
		return 0;
	case 1:
		*sideband_type = SIDEBAND_PRIMARY;
		break;
	default:
		strbuf_addf(scratch, "%s%s: protocol error: bad band #%d",
			    scratch->len ? "\n" : "", me, band);
		*sideband_type = SIDEBAND_PROTOCOL_ERROR;
		break;
	}

cleanup:
	if (die_on_error && *sideband_type == SIDEBAND_PROTOCOL_ERROR)
		die("%s", scratch->buf);
	if (scratch->len) {
		strbuf_addch(scratch, '\n');
		xwrite(2, scratch->buf, scratch->len);
	}
	strbuf_release(scratch);
	return 1;
}