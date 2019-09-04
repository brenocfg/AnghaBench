#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int buf; } ;
struct TYPE_3__ {scalar_t__ nr; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 TYPE_1__ cookies_to_redact ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ skip_prefix (int,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,char const*) ; 
 char* strchrnul (char*,char) ; 
 scalar_t__ string_list_lookup (TYPE_1__*,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void redact_sensitive_header(struct strbuf *header)
{
	const char *sensitive_header;

	if (skip_prefix(header->buf, "Authorization:", &sensitive_header) ||
	    skip_prefix(header->buf, "Proxy-Authorization:", &sensitive_header)) {
		/* The first token is the type, which is OK to log */
		while (isspace(*sensitive_header))
			sensitive_header++;
		while (*sensitive_header && !isspace(*sensitive_header))
			sensitive_header++;
		/* Everything else is opaque and possibly sensitive */
		strbuf_setlen(header,  sensitive_header - header->buf);
		strbuf_addstr(header, " <redacted>");
	} else if (cookies_to_redact.nr &&
		   skip_prefix(header->buf, "Cookie:", &sensitive_header)) {
		struct strbuf redacted_header = STRBUF_INIT;
		char *cookie;

		while (isspace(*sensitive_header))
			sensitive_header++;

		/*
		 * The contents of header starting from sensitive_header will
		 * subsequently be overridden, so it is fine to mutate this
		 * string (hence the assignment to "char *").
		 */
		cookie = (char *) sensitive_header;

		while (cookie) {
			char *equals;
			char *semicolon = strstr(cookie, "; ");
			if (semicolon)
				*semicolon = 0;
			equals = strchrnul(cookie, '=');
			if (!equals) {
				/* invalid cookie, just append and continue */
				strbuf_addstr(&redacted_header, cookie);
				continue;
			}
			*equals = 0; /* temporarily set to NUL for lookup */
			if (string_list_lookup(&cookies_to_redact, cookie)) {
				strbuf_addstr(&redacted_header, cookie);
				strbuf_addstr(&redacted_header, "=<redacted>");
			} else {
				*equals = '=';
				strbuf_addstr(&redacted_header, cookie);
			}
			if (semicolon) {
				/*
				 * There are more cookies. (Or, for some
				 * reason, the input string ends in "; ".)
				 */
				strbuf_addstr(&redacted_header, "; ");
				cookie = semicolon + strlen("; ");
			} else {
				cookie = NULL;
			}
		}

		strbuf_setlen(header, sensitive_header - header->buf);
		strbuf_addbuf(header, &redacted_header);
	}
}