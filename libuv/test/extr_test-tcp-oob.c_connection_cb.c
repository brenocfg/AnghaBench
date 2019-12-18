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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_os_fd_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  MSG_OOB ; 
 int /*<<< orphan*/  alloc_cb ; 
 int /*<<< orphan*/  client_handle ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  peer_handle ; 
 int /*<<< orphan*/  read_cb ; 
 int send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_fileno (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_stream_set_blocking (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void connection_cb(uv_stream_t* handle, int status) {
  int r;
  uv_os_fd_t fd;

  ASSERT(0 == status);
  ASSERT(0 == uv_accept(handle, (uv_stream_t*) &peer_handle));
  ASSERT(0 == uv_read_start((uv_stream_t*) &peer_handle, alloc_cb, read_cb));

  /* Send some OOB data */
  ASSERT(0 == uv_fileno((uv_handle_t*) &client_handle, &fd));

  ASSERT(0 == uv_stream_set_blocking((uv_stream_t*) &client_handle, 1));

  /* The problem triggers only on a second message, it seem that xnu is not
   * triggering `kevent()` for the first one
   */
  do {
    r = send(fd, "hello", 5, MSG_OOB);
  } while (r < 0 && errno == EINTR);
  ASSERT(5 == r);

  do {
    r = send(fd, "hello", 5, MSG_OOB);
  } while (r < 0 && errno == EINTR);
  ASSERT(5 == r);

  ASSERT(0 == uv_stream_set_blocking((uv_stream_t*) &client_handle, 0));
}