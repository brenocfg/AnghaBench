#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ offset; } ;
struct TYPE_15__ {TYPE_2__ info; } ;
struct TYPE_13__ {int fd; } ;
struct TYPE_18__ {TYPE_3__ fs; TYPE_1__ file; } ;
typedef  TYPE_6__ uv_fs_t ;
struct TYPE_17__ {scalar_t__ QuadPart; } ;
struct TYPE_16__ {scalar_t__ QuadPart; int /*<<< orphan*/  LowPart; int /*<<< orphan*/  HighPart; } ;
struct uv__fd_info_s {void* mapping; int flags; TYPE_5__ current_pos; TYPE_4__ size; scalar_t__ is_directory; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {TYPE_4__ EndOfFile; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  void* HANDLE ;
typedef  TYPE_7__ FILE_END_OF_FILE_INFORMATION ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (void*) ; 
 void* CreateFileMapping (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FileEndOfFileInformation ; 
 int /*<<< orphan*/  GetLastError () ; 
 void* INVALID_HANDLE_VALUE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REQ_WIN32_ERROR (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int UV_FS_O_RDONLY ; 
 int UV_FS_O_RDWR ; 
 int UV_FS_O_WRONLY ; 
 int /*<<< orphan*/  VERIFY_FD (int,TYPE_6__*) ; 
 int /*<<< orphan*/  pNtSetInformationFile (void*,int /*<<< orphan*/ *,TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlNtStatusToDosError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__fd_hash_add (int,struct uv__fd_info_s*) ; 
 scalar_t__ uv__fd_hash_get (int,struct uv__fd_info_s*) ; 
 void* uv__get_osfhandle (int) ; 

__attribute__((used)) static void fs__ftruncate(uv_fs_t* req) {
  int fd = req->file.fd;
  HANDLE handle;
  struct uv__fd_info_s fd_info = { 0 };
  NTSTATUS status;
  IO_STATUS_BLOCK io_status;
  FILE_END_OF_FILE_INFORMATION eof_info;

  VERIFY_FD(fd, req);

  handle = uv__get_osfhandle(fd);

  if (uv__fd_hash_get(fd, &fd_info)) {
    if (fd_info.is_directory) {
      SET_REQ_WIN32_ERROR(req, ERROR_ACCESS_DENIED);
      return;
    }

    if (fd_info.mapping != INVALID_HANDLE_VALUE) {
      CloseHandle(fd_info.mapping);
    }
  }

  eof_info.EndOfFile.QuadPart = req->fs.info.offset;

  status = pNtSetInformationFile(handle,
                                 &io_status,
                                 &eof_info,
                                 sizeof eof_info,
                                 FileEndOfFileInformation);

  if (NT_SUCCESS(status)) {
    SET_REQ_RESULT(req, 0);
  } else {
    SET_REQ_WIN32_ERROR(req, pRtlNtStatusToDosError(status));

    if (fd_info.flags) {
      CloseHandle(handle);
      fd_info.mapping = INVALID_HANDLE_VALUE;
      fd_info.size.QuadPart = 0;
      fd_info.current_pos.QuadPart = 0;
      uv__fd_hash_add(fd, &fd_info);
      return;
    }
  }

  if (fd_info.flags) {
    fd_info.size = eof_info.EndOfFile;

    if (fd_info.size.QuadPart == 0) {
      fd_info.mapping = INVALID_HANDLE_VALUE;
    } else {
      DWORD flProtect = (fd_info.flags & (UV_FS_O_RDONLY | UV_FS_O_WRONLY |
        UV_FS_O_RDWR)) == UV_FS_O_RDONLY ? PAGE_READONLY : PAGE_READWRITE;
      fd_info.mapping = CreateFileMapping(handle,
                                          NULL,
                                          flProtect,
                                          fd_info.size.HighPart,
                                          fd_info.size.LowPart,
                                          NULL);
      if (fd_info.mapping == NULL) {
        SET_REQ_WIN32_ERROR(req, GetLastError());
        CloseHandle(handle);
        fd_info.mapping = INVALID_HANDLE_VALUE;
        fd_info.size.QuadPart = 0;
        fd_info.current_pos.QuadPart = 0;
        uv__fd_hash_add(fd, &fd_info);
        return;
      }
    }

    uv__fd_hash_add(fd, &fd_info);
  }
}