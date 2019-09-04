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
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
#define  WHENSPEC_NOW 130 
#define  WHENSPEC_RAW 129 
#define  WHENSPEC_RFC2822 128 
 int /*<<< orphan*/  datestamp (struct strbuf*) ; 
 int /*<<< orphan*/  die (char*,char const*,...) ; 
 int /*<<< orphan*/  parse_date (char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int strcspn (char const*,char*) ; 
 int /*<<< orphan*/  validate_raw_date (char const*,struct strbuf*) ; 
 int whenspec ; 

__attribute__((used)) static char *parse_ident(const char *buf)
{
	const char *ltgt;
	size_t name_len;
	struct strbuf ident = STRBUF_INIT;

	/* ensure there is a space delimiter even if there is no name */
	if (*buf == '<')
		--buf;

	ltgt = buf + strcspn(buf, "<>");
	if (*ltgt != '<')
		die("Missing < in ident string: %s", buf);
	if (ltgt != buf && ltgt[-1] != ' ')
		die("Missing space before < in ident string: %s", buf);
	ltgt = ltgt + 1 + strcspn(ltgt + 1, "<>");
	if (*ltgt != '>')
		die("Missing > in ident string: %s", buf);
	ltgt++;
	if (*ltgt != ' ')
		die("Missing space after > in ident string: %s", buf);
	ltgt++;
	name_len = ltgt - buf;
	strbuf_add(&ident, buf, name_len);

	switch (whenspec) {
	case WHENSPEC_RAW:
		if (validate_raw_date(ltgt, &ident) < 0)
			die("Invalid raw date \"%s\" in ident: %s", ltgt, buf);
		break;
	case WHENSPEC_RFC2822:
		if (parse_date(ltgt, &ident) < 0)
			die("Invalid rfc2822 date \"%s\" in ident: %s", ltgt, buf);
		break;
	case WHENSPEC_NOW:
		if (strcmp("now", ltgt))
			die("Date in ident must be 'now': %s", buf);
		datestamp(&ident);
		break;
	}

	return strbuf_detach(&ident, NULL);
}