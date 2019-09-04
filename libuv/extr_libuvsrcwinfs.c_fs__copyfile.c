#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int file_flags; int /*<<< orphan*/  new_pathw; } ;
struct TYPE_11__ {TYPE_2__ info; } ;
struct TYPE_9__ {int /*<<< orphan*/  pathw; } ;
struct TYPE_12__ {TYPE_3__ fs; TYPE_1__ file; } ;
typedef  TYPE_4__ uv_fs_t ;

/* Variables and functions */
 scalar_t__ CopyFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERROR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REQ_UV_ERROR (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REQ_WIN32_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV_ENOSYS ; 
 int UV_FS_COPYFILE_EXCL ; 
 int UV_FS_COPYFILE_FICLONE_FORCE ; 

__attribute__((used)) static void fs__copyfile(uv_fs_t* req) {
  int flags;
  int overwrite;

  flags = req->fs.info.file_flags;

  if (flags & UV_FS_COPYFILE_FICLONE_FORCE) {
    SET_REQ_UV_ERROR(req, UV_ENOSYS, ERROR_NOT_SUPPORTED);
    return;
  }

  overwrite = flags & UV_FS_COPYFILE_EXCL;

  if (CopyFileW(req->file.pathw, req->fs.info.new_pathw, overwrite) == 0) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    return;
  }

  SET_REQ_RESULT(req, 0);
}