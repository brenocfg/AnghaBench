#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int mode; } ;
struct TYPE_14__ {TYPE_2__ info; } ;
struct TYPE_12__ {int fd; } ;
struct TYPE_15__ {TYPE_3__ fs; TYPE_1__ file; } ;
typedef  TYPE_4__ uv_fs_t ;
struct TYPE_16__ {int FileAttributes; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_5__ FILE_BASIC_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int /*<<< orphan*/  FILE_WRITE_ATTRIBUTES ; 
 int /*<<< orphan*/  FileBasicInformation ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ReOpenFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REQ_SUCCESS (TYPE_4__*) ; 
 int /*<<< orphan*/  SET_REQ_WIN32_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_FD (int,TYPE_4__*) ; 
 int _S_IWRITE ; 
 int /*<<< orphan*/  pNtQueryInformationFile (scalar_t__,int /*<<< orphan*/ *,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtSetInformationFile (scalar_t__,int /*<<< orphan*/ *,TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlNtStatusToDosError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__get_osfhandle (int) ; 

__attribute__((used)) static void fs__fchmod(uv_fs_t* req) {
  int fd = req->file.fd;
  int clear_archive_flag;
  HANDLE handle;
  NTSTATUS nt_status;
  IO_STATUS_BLOCK io_status;
  FILE_BASIC_INFORMATION file_info;

  VERIFY_FD(fd, req);

  handle = ReOpenFile(uv__get_osfhandle(fd), FILE_WRITE_ATTRIBUTES, 0, 0);
  if (handle == INVALID_HANDLE_VALUE) {
    SET_REQ_WIN32_ERROR(req, GetLastError());
    return;
  }

  nt_status = pNtQueryInformationFile(handle,
                                      &io_status,
                                      &file_info,
                                      sizeof file_info,
                                      FileBasicInformation);

  if (!NT_SUCCESS(nt_status)) {
    SET_REQ_WIN32_ERROR(req, pRtlNtStatusToDosError(nt_status));
    goto fchmod_cleanup;
  }

  /* Test if the Archive attribute is cleared */
  if ((file_info.FileAttributes & FILE_ATTRIBUTE_ARCHIVE) == 0) {
      /* Set Archive flag, otherwise setting or clearing the read-only
         flag will not work */
      file_info.FileAttributes |= FILE_ATTRIBUTE_ARCHIVE;
      nt_status = pNtSetInformationFile(handle,
                                        &io_status,
                                        &file_info,
                                        sizeof file_info,
                                        FileBasicInformation);
      if (!NT_SUCCESS(nt_status)) {
        SET_REQ_WIN32_ERROR(req, pRtlNtStatusToDosError(nt_status));
        goto fchmod_cleanup;
      }
      /* Remeber to clear the flag later on */
      clear_archive_flag = 1;
  } else {
      clear_archive_flag = 0;
  }

  if (req->fs.info.mode & _S_IWRITE) {
    file_info.FileAttributes &= ~FILE_ATTRIBUTE_READONLY;
  } else {
    file_info.FileAttributes |= FILE_ATTRIBUTE_READONLY;
  }

  nt_status = pNtSetInformationFile(handle,
                                    &io_status,
                                    &file_info,
                                    sizeof file_info,
                                    FileBasicInformation);

  if (!NT_SUCCESS(nt_status)) {
    SET_REQ_WIN32_ERROR(req, pRtlNtStatusToDosError(nt_status));
    goto fchmod_cleanup;
  }

  if (clear_archive_flag) {
      file_info.FileAttributes &= ~FILE_ATTRIBUTE_ARCHIVE;
      if (file_info.FileAttributes == 0) {
          file_info.FileAttributes = FILE_ATTRIBUTE_NORMAL;
      }
      nt_status = pNtSetInformationFile(handle,
                                        &io_status,
                                        &file_info,
                                        sizeof file_info,
                                        FileBasicInformation);
      if (!NT_SUCCESS(nt_status)) {
        SET_REQ_WIN32_ERROR(req, pRtlNtStatusToDosError(nt_status));
        goto fchmod_cleanup;
      }
  }

  SET_REQ_SUCCESS(req);
fchmod_cleanup:
  CloseHandle(handle);
}