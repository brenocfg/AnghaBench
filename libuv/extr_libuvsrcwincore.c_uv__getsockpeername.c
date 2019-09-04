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
typedef  scalar_t__ uv_os_fd_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int (* uv__peersockfunc ) (int /*<<< orphan*/ ,struct sockaddr*,int*) ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 int WSAGetLastError () ; 
 int uv_fileno (int /*<<< orphan*/  const*,scalar_t__*) ; 
 int uv_translate_sys_error (int) ; 

int uv__getsockpeername(const uv_handle_t* handle,
                        uv__peersockfunc func,
                        struct sockaddr* name,
                        int* namelen,
                        int delayed_error) {

  int result;
  uv_os_fd_t fd;

  result = uv_fileno(handle, &fd);
  if (result != 0)
    return result;

  if (delayed_error)
    return uv_translate_sys_error(delayed_error);

  result = func((SOCKET) fd, name, namelen);
  if (result != 0)
    return uv_translate_sys_error(WSAGetLastError());

  return 0;
}