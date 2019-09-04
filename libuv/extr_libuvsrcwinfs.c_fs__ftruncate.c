#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  offset; } ;
struct TYPE_15__ {TYPE_3__ info; } ;
struct TYPE_12__ {int fd; } ;
struct TYPE_16__ {TYPE_4__ fs; TYPE_1__ file; } ;
typedef  TYPE_5__ uv_fs_t ;
struct TYPE_13__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_17__ {TYPE_2__ EndOfFile; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_6__ FILE_END_OF_FILE_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  FileEndOfFileInformation ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REQ_WIN32_ERROR (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_FD (int,TYPE_5__*) ; 
 int /*<<< orphan*/  pNtSetInformationFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pRtlNtStatusToDosError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__get_osfhandle (int) ; 

__attribute__((used)) static void fs__ftruncate(uv_fs_t* req) {
  int fd = req->file.fd;
  HANDLE handle;
  NTSTATUS status;
  IO_STATUS_BLOCK io_status;
  FILE_END_OF_FILE_INFORMATION eof_info;

  VERIFY_FD(fd, req);

  handle = uv__get_osfhandle(fd);

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
  }
}