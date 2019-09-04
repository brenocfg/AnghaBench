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
struct lock_file {int dummy; } ;

/* Variables and functions */
 int LOCK_DIE_ON_ERROR ; 
 int LOCK_REPORT_ON_ERROR ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int lock_file_timeout (struct lock_file*,char const*,int,long) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  unable_to_lock_die (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unable_to_lock_message (char const*,int /*<<< orphan*/ ,struct strbuf*) ; 

int hold_lock_file_for_update_timeout(struct lock_file *lk, const char *path,
				      int flags, long timeout_ms)
{
	int fd = lock_file_timeout(lk, path, flags, timeout_ms);
	if (fd < 0) {
		if (flags & LOCK_DIE_ON_ERROR)
			unable_to_lock_die(path, errno);
		if (flags & LOCK_REPORT_ON_ERROR) {
			struct strbuf buf = STRBUF_INIT;
			unable_to_lock_message(path, errno, &buf);
			error("%s", buf.buf);
			strbuf_release(&buf);
		}
	}
	return fd;
}