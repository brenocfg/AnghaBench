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
 int /*<<< orphan*/  redact_sensitive_header (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,long,long) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int,char const*,int) ; 
 int /*<<< orphan*/  strbuf_list_free (struct strbuf**) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 struct strbuf** strbuf_split_max (struct strbuf*,char,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  trace_curl ; 
 int /*<<< orphan*/  trace_strbuf (int /*<<< orphan*/ *,struct strbuf*) ; 

__attribute__((used)) static void curl_dump_header(const char *text, unsigned char *ptr, size_t size, int hide_sensitive_header)
{
	struct strbuf out = STRBUF_INIT;
	struct strbuf **headers, **header;

	strbuf_addf(&out, "%s, %10.10ld bytes (0x%8.8lx)\n",
		text, (long)size, (long)size);
	trace_strbuf(&trace_curl, &out);
	strbuf_reset(&out);
	strbuf_add(&out, ptr, size);
	headers = strbuf_split_max(&out, '\n', 0);

	for (header = headers; *header; header++) {
		if (hide_sensitive_header)
			redact_sensitive_header(*header);
		strbuf_insert((*header), 0, text, strlen(text));
		strbuf_insert((*header), strlen(text), ": ", 2);
		strbuf_rtrim((*header));
		strbuf_addch((*header), '\n');
		trace_strbuf(&trace_curl, (*header));
	}
	strbuf_list_free(headers);
	strbuf_release(&out);
}