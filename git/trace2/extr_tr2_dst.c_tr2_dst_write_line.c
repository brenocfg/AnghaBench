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
struct tr2_dst {int /*<<< orphan*/  sysenv_var; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strbuf_complete_line (struct strbuf*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int tr2_dst_get_trace_fd (struct tr2_dst*) ; 
 int /*<<< orphan*/  tr2_dst_trace_disable (struct tr2_dst*) ; 
 scalar_t__ tr2_dst_want_warning () ; 
 int /*<<< orphan*/  tr2_sysenv_display_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tr2_dst_write_line(struct tr2_dst *dst, struct strbuf *buf_line)
{
	int fd = tr2_dst_get_trace_fd(dst);

	strbuf_complete_line(buf_line); /* ensure final NL on buffer */

	/*
	 * We do not use write_in_full() because we do not want
	 * a short-write to try again.  We are using O_APPEND mode
	 * files and the kernel handles the atomic seek+write. If
	 * another thread or git process is concurrently writing to
	 * this fd or file, our remainder-write may not be contiguous
	 * with our initial write of this message.  And that will
	 * confuse readers.  So just don't bother.
	 *
	 * It is assumed that TRACE2 messages are short enough that
	 * the system can write them in 1 attempt and we won't see
	 * a short-write.
	 *
	 * If we get an IO error, just close the trace dst.
	 */
	if (write(fd, buf_line->buf, buf_line->len) >= 0)
		return;

	if (tr2_dst_want_warning())
		warning("unable to write trace to '%s': %s",
			tr2_sysenv_display_name(dst->sysenv_var),
			strerror(errno));
	tr2_dst_trace_disable(dst);
}