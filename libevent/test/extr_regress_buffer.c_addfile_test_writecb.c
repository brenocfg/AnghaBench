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
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int) ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 int addfile_test_done_writing ; 
 int /*<<< orphan*/  addfile_test_event_base ; 
 int addfile_test_total_written ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_validate (struct evbuffer*) ; 
 int evbuffer_write (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int evutil_socket_geterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_fail_perror (char*) ; 

__attribute__((used)) static void
addfile_test_writecb(evutil_socket_t fd, short what, void *arg)
{
	struct evbuffer *b = arg;
	int r;
	evbuffer_validate(b);
	while (evbuffer_get_length(b)) {
		r = evbuffer_write(b, fd);
		if (r > 0) {
			addfile_test_total_written += r;
			TT_BLATHER(("Wrote %d/%d bytes", r, addfile_test_total_written));
		} else {
			int e = evutil_socket_geterror(fd);
			if (EVUTIL_ERR_RW_RETRIABLE(e))
				return;
			tt_fail_perror("write");
			event_base_loopexit(addfile_test_event_base,NULL);
		}
		evbuffer_validate(b);
	}
	addfile_test_done_writing = 1;
	return;
end:
	event_base_loopexit(addfile_test_event_base,NULL);
}