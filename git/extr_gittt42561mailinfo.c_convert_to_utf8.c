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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct mailinfo {char* metainfo_charset; int input_error; } ;

/* Variables and functions */
 int error (char*,char const*,char*) ; 
 char* reencode_string (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ same_encoding (char*,char const*) ; 
 int /*<<< orphan*/  strbuf_attach (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int convert_to_utf8(struct mailinfo *mi,
			   struct strbuf *line, const char *charset)
{
	char *out;

	if (!mi->metainfo_charset || !charset || !*charset)
		return 0;

	if (same_encoding(mi->metainfo_charset, charset))
		return 0;
	out = reencode_string(line->buf, mi->metainfo_charset, charset);
	if (!out) {
		mi->input_error = -1;
		return error("cannot convert from %s to %s",
			     charset, mi->metainfo_charset);
	}
	strbuf_attach(line, out, strlen(out), strlen(out));
	return 0;
}