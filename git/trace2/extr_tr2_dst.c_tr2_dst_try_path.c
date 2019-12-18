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
struct tr2_dst {int fd; int need_close; int initialized; int /*<<< orphan*/  sysenv_var; } ;

/* Variables and functions */
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr2_dst_trace_disable (struct tr2_dst*) ; 
 scalar_t__ tr2_dst_want_warning () ; 
 int /*<<< orphan*/  tr2_sysenv_display_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tr2_dst_try_path(struct tr2_dst *dst, const char *tgt_value)
{
	int fd = open(tgt_value, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == -1) {
		if (tr2_dst_want_warning())
			warning("trace2: could not open '%s' for '%s' tracing: %s",
				tgt_value,
				tr2_sysenv_display_name(dst->sysenv_var),
				strerror(errno));

		tr2_dst_trace_disable(dst);
		return 0;
	}

	dst->fd = fd;
	dst->need_close = 1;
	dst->initialized = 1;

	return dst->fd;
}