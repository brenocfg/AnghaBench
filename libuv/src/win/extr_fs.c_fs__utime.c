#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; } ;
struct TYPE_7__ {TYPE_3__ time; } ;
struct TYPE_8__ {int /*<<< orphan*/  pathw; } ;
struct TYPE_10__ {scalar_t__ result; TYPE_1__ fs; TYPE_2__ file; } ;
typedef  TYPE_4__ uv_fs_t ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FILE_WRITE_ATTRIBUTES ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SET_REQ_WIN32_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fs__utime_handle (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs__utime(uv_fs_t* req) {
  HANDLE handle;

  handle = CreateFileW(req->file.pathw,
                       FILE_WRITE_ATTRIBUTES,
                       FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                       NULL,
                       OPEN_EXISTING,
                       FILE_FLAG_BACKUP_SEMANTICS,
                       NULL);

  if (handle == INVALID_HANDLE_VALUE) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    return;
  }

  if (fs__utime_handle(handle, req->fs.time.atime, req->fs.time.mtime) != 0) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    CloseHandle(handle);
    return;
  }

  CloseHandle(handle);

  req->result = 0;
}