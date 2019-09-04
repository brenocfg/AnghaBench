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
typedef  int /*<<< orphan*/  uv_handle_type ;
struct sockaddr_storage {int ss_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int /*<<< orphan*/  UV_NAMED_PIPE ; 
 int /*<<< orphan*/  UV_TCP ; 
 int /*<<< orphan*/  UV_UDP ; 
 int /*<<< orphan*/  UV_UNKNOWN_HANDLE ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 

uv_handle_type uv__handle_type(int fd) {
  struct sockaddr_storage ss;
  socklen_t sslen;
  socklen_t len;
  int type;

  memset(&ss, 0, sizeof(ss));
  sslen = sizeof(ss);

  if (getsockname(fd, (struct sockaddr*)&ss, &sslen))
    return UV_UNKNOWN_HANDLE;

  len = sizeof type;

  if (getsockopt(fd, SOL_SOCKET, SO_TYPE, &type, &len))
    return UV_UNKNOWN_HANDLE;

  if (type == SOCK_STREAM) {
#if defined(_AIX) || defined(__DragonFly__)
    /* on AIX/DragonFly the getsockname call returns an empty sa structure
     * for sockets of type AF_UNIX.  For all other types it will
     * return a properly filled in structure.
     */
    if (sslen == 0)
      return UV_NAMED_PIPE;
#endif
    switch (ss.ss_family) {
      case AF_UNIX:
        return UV_NAMED_PIPE;
      case AF_INET:
      case AF_INET6:
        return UV_TCP;
      }
  }

  if (type == SOCK_DGRAM &&
      (ss.ss_family == AF_INET || ss.ss_family == AF_INET6))
    return UV_UDP;

  return UV_UNKNOWN_HANDLE;
}