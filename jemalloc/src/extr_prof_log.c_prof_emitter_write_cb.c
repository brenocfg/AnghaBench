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
struct prof_emitter_cb_arg_s {int /*<<< orphan*/  fd; int /*<<< orphan*/  ret; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc_write_fd (int /*<<< orphan*/ ,char const*,size_t) ; 
 scalar_t__ prof_log_dummy ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
prof_emitter_write_cb(void *opaque, const char *to_write) {
	struct prof_emitter_cb_arg_s *arg =
	    (struct prof_emitter_cb_arg_s *)opaque;
	size_t bytes = strlen(to_write);
#ifdef JEMALLOC_JET
	if (prof_log_dummy) {
		return;
	}
#endif
	arg->ret = malloc_write_fd(arg->fd, to_write, bytes);
}