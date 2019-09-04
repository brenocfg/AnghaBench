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
typedef  int /*<<< orphan*/  va_list ;
struct strbuf {size_t len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 size_t LARGE_PACKET_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_trace (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  set_packet_header (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_vaddf (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void format_packet(struct strbuf *out, const char *prefix,
			  const char *fmt, va_list args)
{
	size_t orig_len, n;

	orig_len = out->len;
	strbuf_addstr(out, "0000");
	strbuf_addstr(out, prefix);
	strbuf_vaddf(out, fmt, args);
	n = out->len - orig_len;

	if (n > LARGE_PACKET_MAX)
		die(_("protocol error: impossibly long line"));

	set_packet_header(&out->buf[orig_len], n);
	packet_trace(out->buf + orig_len + 4, n - 4, 1);
}