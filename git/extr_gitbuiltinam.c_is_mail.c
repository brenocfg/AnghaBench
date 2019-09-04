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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  SEEK_SET ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int is_mail(FILE *fp)
{
	const char *header_regex = "^[!-9;-~]+:";
	struct strbuf sb = STRBUF_INIT;
	regex_t regex;
	int ret = 1;

	if (fseek(fp, 0L, SEEK_SET))
		die_errno(_("fseek failed"));

	if (regcomp(&regex, header_regex, REG_NOSUB | REG_EXTENDED))
		die("invalid pattern: %s", header_regex);

	while (!strbuf_getline(&sb, fp)) {
		if (!sb.len)
			break; /* End of header */

		/* Ignore indented folded lines */
		if (*sb.buf == '\t' || *sb.buf == ' ')
			continue;

		/* It's a header if it matches header_regex */
		if (regexec(&regex, sb.buf, 0, NULL, 0)) {
			ret = 0;
			goto done;
		}
	}

done:
	regfree(&regex);
	strbuf_release(&sb);
	return ret;
}