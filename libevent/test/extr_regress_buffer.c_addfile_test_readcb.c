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
 int /*<<< orphan*/  EVUTIL_ERR_RW_RETRIABLE (int) ; 
 int /*<<< orphan*/  TT_BLATHER (char*) ; 
 scalar_t__ addfile_test_done_writing ; 
 int /*<<< orphan*/  addfile_test_event_base ; 
 scalar_t__ addfile_test_total_read ; 
 scalar_t__ addfile_test_total_written ; 
 int evbuffer_read (struct evbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_base_loopexit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int evutil_socket_geterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_fail_perror (char*) ; 

__attribute__((used)) static void
addfile_test_readcb(evutil_socket_t fd, short what, void *arg)
{
	struct evbuffer *b = arg;
	int e, r = 0;
	do {
		r = evbuffer_read(b, fd, 1024);
		if (r > 0) {
			addfile_test_total_read += r;
			TT_BLATHER(("Read %d/%d bytes", r, addfile_test_total_read));
		}
	} while (r > 0);
	if (r < 0) {
		e = evutil_socket_geterror(fd);
		if (! EVUTIL_ERR_RW_RETRIABLE(e)) {
			tt_fail_perror("read");
			event_base_loopexit(addfile_test_event_base,NULL);
		}
	}
	if (addfile_test_done_writing &&
	    addfile_test_total_read >= addfile_test_total_written) {
		event_base_loopexit(addfile_test_event_base,NULL);
	}
}