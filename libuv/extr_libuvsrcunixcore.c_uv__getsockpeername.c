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
typedef  int /*<<< orphan*/  uv_os_fd_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  scalar_t__ (* uv__peersockfunc ) (int /*<<< orphan*/ ,struct sockaddr*,scalar_t__*) ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int uv_fileno (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int uv__getsockpeername(const uv_handle_t* handle,
                        uv__peersockfunc func,
                        struct sockaddr* name,
                        int* namelen) {
  socklen_t socklen;
  uv_os_fd_t fd;
  int r;

  r = uv_fileno(handle, &fd);
  if (r < 0)
    return r;

  /* sizeof(socklen_t) != sizeof(int) on some systems. */
  socklen = (socklen_t) *namelen;

  if (func(fd, name, &socklen))
    return UV__ERR(errno);

  *namelen = (int) socklen;
  return 0;
}