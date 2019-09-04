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
typedef  size_t uintmax_t ;
struct strbuf {scalar_t__ len; } ;
struct line_buffer {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 size_t buffer_read_binary (struct line_buffer*,struct strbuf*,size_t) ; 
 int error_short_read (struct line_buffer*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static int read_chunk(struct line_buffer *delta, off_t *delta_len,
		      struct strbuf *buf, size_t len)
{
	assert(*delta_len >= 0);
	strbuf_reset(buf);
	if (len > (uintmax_t) *delta_len ||
	    buffer_read_binary(delta, buf, len) != len)
		return error_short_read(delta);
	*delta_len -= buf->len;
	return 0;
}