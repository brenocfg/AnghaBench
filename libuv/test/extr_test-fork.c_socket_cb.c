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
typedef  int /*<<< orphan*/  uv_poll_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_READABLE ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ read (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  socket_cb_called ; 
 int /*<<< orphan*/  socket_cb_read_buf ; 
 scalar_t__ socket_cb_read_fd ; 
 scalar_t__ socket_cb_read_size ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void socket_cb(uv_poll_t* poll, int status, int events) {
  ssize_t cnt;
  socket_cb_called++;
  ASSERT(0 == status);
  printf("Socket cb got events %d\n", events);
  ASSERT(UV_READABLE == (events & UV_READABLE));
  if (socket_cb_read_fd) {
    cnt = read(socket_cb_read_fd, socket_cb_read_buf, socket_cb_read_size);
    ASSERT(cnt == socket_cb_read_size);
  }
  uv_close((uv_handle_t*) poll, NULL);
}