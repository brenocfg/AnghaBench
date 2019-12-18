#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fd; } ;
struct TYPE_7__ {scalar_t__ result; TYPE_1__ file; } ;
typedef  TYPE_2__ uv_fs_t ;
struct uv__fd_info_s {scalar_t__ mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ EBADF ; 
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SET_REQ_UV_ERROR (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV_EBADF ; 
 int /*<<< orphan*/  VERIFY_FD (int,TYPE_2__*) ; 
 int _close (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 scalar_t__ uv__fd_hash_remove (int,struct uv__fd_info_s*) ; 

void fs__close(uv_fs_t* req) {
  int fd = req->file.fd;
  int result;
  struct uv__fd_info_s fd_info;

  VERIFY_FD(fd, req);

  if (uv__fd_hash_remove(fd, &fd_info)) {
    if (fd_info.mapping != INVALID_HANDLE_VALUE) {
      CloseHandle(fd_info.mapping);
    }
  }

  if (fd > 2)
    result = _close(fd);
  else
    result = 0;

  /* _close doesn't set _doserrno on failure, but it does always set errno
   * to EBADF on failure.
   */
  if (result == -1) {
    assert(errno == EBADF);
    SET_REQ_UV_ERROR(req, UV_EBADF, ERROR_INVALID_HANDLE);
  } else {
    req->result = 0;
  }
}