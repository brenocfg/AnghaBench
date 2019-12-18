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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  MSG_OOB ; 
 int UV_PRIORITIZED ; 
 int UV_READABLE ; 
 int UV_WRITABLE ; 
 int cli_pr_check ; 
 int cli_rd_check ; 
 int client_fd ; 
 scalar_t__ errno ; 
 int got_eagain () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * poll_req ; 
 int recv (int,char**,int,int /*<<< orphan*/ ) ; 
 int send (int,char*,int,int /*<<< orphan*/ ) ; 
 int server_fd ; 
 int srv_rd_check ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ uv_fileno (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ uv_poll_start (int /*<<< orphan*/ *,int,void (*) (int /*<<< orphan*/ *,int,int)) ; 
 scalar_t__ uv_poll_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void poll_cb(uv_poll_t* handle, int status, int events) {
  char buffer[5];
  int n;
  int fd;

  ASSERT(0 == uv_fileno((uv_handle_t*)handle, &fd));
  memset(buffer, 0, 5);

  if (events & UV_PRIORITIZED) {
    do
      n = recv(client_fd, &buffer, 5, MSG_OOB);
    while (n == -1 && errno == EINTR);
    ASSERT(n >= 0 || errno != EINVAL);
    cli_pr_check = 1;
    ASSERT(0 == uv_poll_stop(&poll_req[0]));
    ASSERT(0 == uv_poll_start(&poll_req[0],
                              UV_READABLE | UV_WRITABLE,
                              poll_cb));
  }
  if (events & UV_READABLE) {
    if (fd == client_fd) {
      do
        n = recv(client_fd, &buffer, 5, 0);
      while (n == -1 && errno == EINTR);
      ASSERT(n >= 0 || errno != EINVAL);
      if (cli_rd_check == 1) {
        ASSERT(strncmp(buffer, "world", n) == 0);
        ASSERT(5 == n);
        cli_rd_check = 2;
      }
      if (cli_rd_check == 0) {
        ASSERT(n == 4);
        ASSERT(strncmp(buffer, "hello", n) == 0);
        cli_rd_check = 1;
        do {
          do
            n = recv(server_fd, &buffer, 5, 0);
          while (n == -1 && errno == EINTR);
          if (n > 0) {
            ASSERT(n == 5);
            ASSERT(strncmp(buffer, "world", n) == 0);
            cli_rd_check = 2;
          }
        } while (n > 0);

        ASSERT(got_eagain());
      }
    }
    if (fd == server_fd) {
      do
        n = recv(server_fd, &buffer, 3, 0);
      while (n == -1 && errno == EINTR);
      ASSERT(n >= 0 || errno != EINVAL);
      ASSERT(3 == n);
      ASSERT(strncmp(buffer, "foo", n) == 0);
      srv_rd_check = 1;
      uv_poll_stop(&poll_req[1]);
    }
  }
  if (events & UV_WRITABLE) {
    do {
      n = send(client_fd, "foo", 3, 0);
    } while (n < 0 && errno == EINTR);
    ASSERT(3 == n);
  }
}