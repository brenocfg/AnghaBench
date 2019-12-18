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
struct TYPE_6__ {int /*<<< orphan*/  pathw; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  ptr; TYPE_1__ file; } ;
typedef  TYPE_2__ uv_fs_t ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int FILE_FLAG_BACKUP_SEMANTICS ; 
 int FILE_FLAG_OPEN_REPARSE_POINT ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REQ_WIN32_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV_FS_FREE_PTR ; 
 scalar_t__ fs__readlink_handle (scalar_t__,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fs__readlink(uv_fs_t* req) {
  HANDLE handle;

  handle = CreateFileW(req->file.pathw,
                       0,
                       0,
                       NULL,
                       OPEN_EXISTING,
                       FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS,
                       NULL);

  if (handle == INVALID_HANDLE_VALUE) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    return;
  }

  if (fs__readlink_handle(handle, (char**) &req->ptr, NULL) != 0) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    CloseHandle(handle);
    return;
  }

  req->flags |= UV_FS_FREE_PTR;
  SET_REQ_RESULT(req, 0);

  CloseHandle(handle);
}