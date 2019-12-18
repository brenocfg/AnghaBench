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
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  saddr ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 unsigned long UV_HANDLE_BOUND ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int uv__socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__stream_fd (int /*<<< orphan*/ *) ; 
 int uv__stream_open (int /*<<< orphan*/ *,int,unsigned long) ; 

__attribute__((used)) static int new_socket(uv_tcp_t* handle, int domain, unsigned long flags) {
  struct sockaddr_storage saddr;
  socklen_t slen;
  int sockfd;
  int err;

  err = uv__socket(domain, SOCK_STREAM, 0);
  if (err < 0)
    return err;
  sockfd = err;

  err = uv__stream_open((uv_stream_t*) handle, sockfd, flags);
  if (err) {
    uv__close(sockfd);
    return err;
  }

  if (flags & UV_HANDLE_BOUND) {
    /* Bind this new socket to an arbitrary port */
    slen = sizeof(saddr);
    memset(&saddr, 0, sizeof(saddr));
    if (getsockname(uv__stream_fd(handle), (struct sockaddr*) &saddr, &slen)) {
      uv__close(sockfd);
      return UV__ERR(errno);
    }

    if (bind(uv__stream_fd(handle), (struct sockaddr*) &saddr, slen)) {
      uv__close(sockfd);
      return UV__ERR(errno);
    }
  }

  return 0;
}