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
typedef  scalar_t__ uv_file ;
typedef  int /*<<< orphan*/  type ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNIX ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TYPE ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV_FILE ; 
 int /*<<< orphan*/  UV_NAMED_PIPE ; 
 int /*<<< orphan*/  UV_TCP ; 
 int /*<<< orphan*/  UV_TTY ; 
 int /*<<< orphan*/  UV_UDP ; 
 int /*<<< orphan*/  UV_UNKNOWN_HANDLE ; 
 scalar_t__ fstat (scalar_t__,struct stat*) ; 
 scalar_t__ getsockname (scalar_t__,struct sockaddr*,int*) ; 
 scalar_t__ getsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ isatty (scalar_t__) ; 

uv_handle_type uv_guess_handle(uv_file file) {
  struct sockaddr sa;
  struct stat s;
  socklen_t len;
  int type;

  if (file < 0)
    return UV_UNKNOWN_HANDLE;

  if (isatty(file))
    return UV_TTY;

  if (fstat(file, &s))
    return UV_UNKNOWN_HANDLE;

  if (S_ISREG(s.st_mode))
    return UV_FILE;

  if (S_ISCHR(s.st_mode))
    return UV_FILE;  /* XXX UV_NAMED_PIPE? */

  if (S_ISFIFO(s.st_mode))
    return UV_NAMED_PIPE;

  if (!S_ISSOCK(s.st_mode))
    return UV_UNKNOWN_HANDLE;

  len = sizeof(type);
  if (getsockopt(file, SOL_SOCKET, SO_TYPE, &type, &len))
    return UV_UNKNOWN_HANDLE;

  len = sizeof(sa);
  if (getsockname(file, &sa, &len))
    return UV_UNKNOWN_HANDLE;

  if (type == SOCK_DGRAM)
    if (sa.sa_family == AF_INET || sa.sa_family == AF_INET6)
      return UV_UDP;

  if (type == SOCK_STREAM) {
#if defined(_AIX) || defined(__DragonFly__)
    /* on AIX/DragonFly the getsockname call returns an empty sa structure
     * for sockets of type AF_UNIX.  For all other types it will
     * return a properly filled in structure.
     */
    if (len == 0)
      return UV_NAMED_PIPE;
#endif /* defined(_AIX) || defined(__DragonFly__) */

    if (sa.sa_family == AF_INET || sa.sa_family == AF_INET6)
      return UV_TCP;
    if (sa.sa_family == AF_UNIX)
      return UV_NAMED_PIPE;
  }

  return UV_UNKNOWN_HANDLE;
}