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
struct TYPE_7__ {scalar_t__ result; int /*<<< orphan*/  statbuf; int /*<<< orphan*/ * ptr; TYPE_1__ file; } ;
typedef  TYPE_2__ uv_fs_t ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SET_REQ_WIN32_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_FD (int,TYPE_2__*) ; 
 scalar_t__ fs__stat_handle (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv__get_osfhandle (int) ; 

__attribute__((used)) static void fs__fstat(uv_fs_t* req) {
  int fd = req->file.fd;
  HANDLE handle;

  VERIFY_FD(fd, req);

  handle = uv__get_osfhandle(fd);

  if (handle == INVALID_HANDLE_VALUE) {
    SET_REQ_WIN32_ERROR(req, ERROR_INVALID_HANDLE);
    return;
  }

  if (fs__stat_handle(handle, &req->statbuf, 0) != 0) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    return;
  }

  req->ptr = &req->statbuf;
  req->result = 0;
}