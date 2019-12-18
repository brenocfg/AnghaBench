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
struct strbuf {size_t len; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 size_t LARGE_PACKET_MAX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_trace (char const*,size_t,int) ; 
 int /*<<< orphan*/  set_packet_header (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

void packet_buf_write_len(struct strbuf *buf, const char *data, size_t len)
{
	size_t orig_len, n;

	orig_len = buf->len;
	strbuf_addstr(buf, "0000");
	strbuf_add(buf, data, len);
	n = buf->len - orig_len;

	if (n > LARGE_PACKET_MAX)
		die(_("protocol error: impossibly long line"));

	set_packet_header(&buf->buf[orig_len], n);
	packet_trace(data, len, 1);
}