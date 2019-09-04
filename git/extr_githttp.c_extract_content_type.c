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

/* Variables and functions */
 int /*<<< orphan*/  extract_param (char const*,char*,struct strbuf*) ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  tolower (char const) ; 

__attribute__((used)) static void extract_content_type(struct strbuf *raw, struct strbuf *type,
				 struct strbuf *charset)
{
	const char *p;

	strbuf_reset(type);
	strbuf_grow(type, raw->len);
	for (p = raw->buf; *p; p++) {
		if (isspace(*p))
			continue;
		if (*p == ';') {
			p++;
			break;
		}
		strbuf_addch(type, tolower(*p));
	}

	if (!charset)
		return;

	strbuf_reset(charset);
	while (*p) {
		while (isspace(*p) || *p == ';')
			p++;
		if (!extract_param(p, "charset", charset))
			return;
		while (*p && !isspace(*p))
			p++;
	}

	if (!charset->len && starts_with(type->buf, "text/"))
		strbuf_addstr(charset, "ISO-8859-1");
}