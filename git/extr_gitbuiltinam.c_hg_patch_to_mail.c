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
typedef  int /*<<< orphan*/  timestamp_t ;
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFC2822 ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ errno ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int labs (long) ; 
 int /*<<< orphan*/  parse_timestamp (char const*,char**,int) ; 
 char* show_date (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 scalar_t__ starts_with (char*,char*) ; 
 scalar_t__ strbuf_fread (struct strbuf*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static int hg_patch_to_mail(FILE *out, FILE *in, int keep_cr)
{
	struct strbuf sb = STRBUF_INIT;
	int rc = 0;

	while (!strbuf_getline_lf(&sb, in)) {
		const char *str;

		if (skip_prefix(sb.buf, "# User ", &str))
			fprintf(out, "From: %s\n", str);
		else if (skip_prefix(sb.buf, "# Date ", &str)) {
			timestamp_t timestamp;
			long tz, tz2;
			char *end;

			errno = 0;
			timestamp = parse_timestamp(str, &end, 10);
			if (errno) {
				rc = error(_("invalid timestamp"));
				goto exit;
			}

			if (!skip_prefix(end, " ", &str)) {
				rc = error(_("invalid Date line"));
				goto exit;
			}

			errno = 0;
			tz = strtol(str, &end, 10);
			if (errno) {
				rc = error(_("invalid timezone offset"));
				goto exit;
			}

			if (*end) {
				rc = error(_("invalid Date line"));
				goto exit;
			}

			/*
			 * mercurial's timezone is in seconds west of UTC,
			 * however git's timezone is in hours + minutes east of
			 * UTC. Convert it.
			 */
			tz2 = labs(tz) / 3600 * 100 + labs(tz) % 3600 / 60;
			if (tz > 0)
				tz2 = -tz2;

			fprintf(out, "Date: %s\n", show_date(timestamp, tz2, DATE_MODE(RFC2822)));
		} else if (starts_with(sb.buf, "# ")) {
			continue;
		} else {
			fprintf(out, "\n%s\n", sb.buf);
			break;
		}
	}

	strbuf_reset(&sb);
	while (strbuf_fread(&sb, 8192, in) > 0) {
		fwrite(sb.buf, 1, sb.len, out);
		strbuf_reset(&sb);
	}
exit:
	strbuf_release(&sb);
	return rc;
}