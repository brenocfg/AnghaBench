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
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  trace_curl ; 
 int /*<<< orphan*/  trace_strbuf (int /*<<< orphan*/ *,struct strbuf*) ; 

__attribute__((used)) static void curl_dump_data(const char *text, unsigned char *ptr, size_t size)
{
	size_t i;
	struct strbuf out = STRBUF_INIT;
	unsigned int width = 60;

	strbuf_addf(&out, "%s, %10.10ld bytes (0x%8.8lx)\n",
		text, (long)size, (long)size);
	trace_strbuf(&trace_curl, &out);

	for (i = 0; i < size; i += width) {
		size_t w;

		strbuf_reset(&out);
		strbuf_addf(&out, "%s: ", text);
		for (w = 0; (w < width) && (i + w < size); w++) {
			unsigned char ch = ptr[i + w];

			strbuf_addch(&out,
				       (ch >= 0x20) && (ch < 0x80)
				       ? ch : '.');
		}
		strbuf_addch(&out, '\n');
		trace_strbuf(&trace_curl, &out);
	}
	strbuf_release(&out);
}