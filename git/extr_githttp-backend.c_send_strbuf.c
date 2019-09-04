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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  content_length ; 
 int /*<<< orphan*/  content_type ; 
 int /*<<< orphan*/  end_headers (struct strbuf*) ; 
 int /*<<< orphan*/  hdr_int (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdr_str (struct strbuf*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  write_or_die (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_strbuf(struct strbuf *hdr,
			const char *type, struct strbuf *buf)
{
	hdr_int(hdr, content_length, buf->len);
	hdr_str(hdr, content_type, type);
	end_headers(hdr);
	write_or_die(1, buf->buf, buf->len);
}