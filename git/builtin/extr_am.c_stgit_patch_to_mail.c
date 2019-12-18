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
struct strbuf {char const* buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 scalar_t__ str_isspace (char const*) ; 
 scalar_t__ strbuf_fread (struct strbuf*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static int stgit_patch_to_mail(FILE *out, FILE *in, int keep_cr)
{
	struct strbuf sb = STRBUF_INIT;
	int subject_printed = 0;

	while (!strbuf_getline_lf(&sb, in)) {
		const char *str;

		if (str_isspace(sb.buf))
			continue;
		else if (skip_prefix(sb.buf, "Author:", &str))
			fprintf(out, "From:%s\n", str);
		else if (starts_with(sb.buf, "From") || starts_with(sb.buf, "Date"))
			fprintf(out, "%s\n", sb.buf);
		else if (!subject_printed) {
			fprintf(out, "Subject: %s\n", sb.buf);
			subject_printed = 1;
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

	strbuf_release(&sb);
	return 0;
}