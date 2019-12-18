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
 scalar_t__ is_encoding_utf8 (char const*) ; 
 int /*<<< orphan*/  starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,scalar_t__,scalar_t__) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,size_t,size_t) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,scalar_t__,scalar_t__,char const*,scalar_t__) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *replace_encoding_header(char *buf, const char *encoding)
{
	struct strbuf tmp = STRBUF_INIT;
	size_t start, len;
	char *cp = buf;

	/* guess if there is an encoding header before a \n\n */
	while (!starts_with(cp, "encoding ")) {
		cp = strchr(cp, '\n');
		if (!cp || *++cp == '\n')
			return buf;
	}
	start = cp - buf;
	cp = strchr(cp, '\n');
	if (!cp)
		return buf; /* should not happen but be defensive */
	len = cp + 1 - (buf + start);

	strbuf_attach(&tmp, buf, strlen(buf), strlen(buf) + 1);
	if (is_encoding_utf8(encoding)) {
		/* we have re-coded to UTF-8; drop the header */
		strbuf_remove(&tmp, start, len);
	} else {
		/* just replaces XXXX in 'encoding XXXX\n' */
		strbuf_splice(&tmp, start + strlen("encoding "),
					  len - strlen("encoding \n"),
					  encoding, strlen(encoding));
	}
	return strbuf_detach(&tmp, NULL);
}