#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int offset; unsigned int nbufs; TYPE_2__* bufs; } ;
struct TYPE_20__ {TYPE_3__ info; } ;
struct TYPE_17__ {int fd; } ;
struct TYPE_21__ {TYPE_4__ fs; TYPE_1__ file; } ;
typedef  TYPE_5__ uv_fs_t ;
struct uv__fd_info_s {int dummy; } ;
typedef  int int64_t ;
struct TYPE_23__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; scalar_t__ QuadPart; } ;
struct TYPE_22__ {int /*<<< orphan*/  OffsetHigh; int /*<<< orphan*/  Offset; } ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_6__ OVERLAPPED ;
typedef  TYPE_7__ LARGE_INTEGER ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_HANDLE_EOF ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int ReadFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,TYPE_6__*) ; 
 int /*<<< orphan*/  SET_REQ_RESULT (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  SET_REQ_WIN32_ERROR (TYPE_5__*,scalar_t__) ; 
 scalar_t__ SetFilePointerEx (scalar_t__,TYPE_7__,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_FD (int,TYPE_5__*) ; 
 int /*<<< orphan*/  fs__read_filemap (TYPE_5__*,struct uv__fd_info_s*) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uv__fd_hash_get (int,struct uv__fd_info_s*) ; 
 scalar_t__ uv__get_osfhandle (int) ; 

void fs__read(uv_fs_t* req) {
  int fd = req->file.fd;
  int64_t offset = req->fs.info.offset;
  HANDLE handle;
  OVERLAPPED overlapped, *overlapped_ptr;
  LARGE_INTEGER offset_;
  DWORD bytes;
  DWORD error;
  int result;
  unsigned int index;
  LARGE_INTEGER original_position;
  LARGE_INTEGER zero_offset;
  int restore_position;
  struct uv__fd_info_s fd_info;

  VERIFY_FD(fd, req);

  if (uv__fd_hash_get(fd, &fd_info)) {
    fs__read_filemap(req, &fd_info);
    return;
  }

  zero_offset.QuadPart = 0;
  restore_position = 0;
  handle = uv__get_osfhandle(fd);

  if (handle == INVALID_HANDLE_VALUE) {
    SET_REQ_WIN32_ERROR(req, ERROR_INVALID_HANDLE);
    return;
  }

  if (offset != -1) {
    memset(&overlapped, 0, sizeof overlapped);
    overlapped_ptr = &overlapped;
    if (SetFilePointerEx(handle, zero_offset, &original_position,
                         FILE_CURRENT)) {
      restore_position = 1;
    }
  } else {
    overlapped_ptr = NULL;
  }

  index = 0;
  bytes = 0;
  do {
    DWORD incremental_bytes;

    if (offset != -1) {
      offset_.QuadPart = offset + bytes;
      overlapped.Offset = offset_.LowPart;
      overlapped.OffsetHigh = offset_.HighPart;
    }

    result = ReadFile(handle,
                      req->fs.info.bufs[index].base,
                      req->fs.info.bufs[index].len,
                      &incremental_bytes,
                      overlapped_ptr);
    bytes += incremental_bytes;
    ++index;
  } while (result && index < req->fs.info.nbufs);

  if (restore_position)
    SetFilePointerEx(handle, original_position, NULL, FILE_BEGIN);

  if (result || bytes > 0) {
    SET_REQ_RESULT(req, bytes);
  } else {
    error = GetLastError();
    if (error == ERROR_HANDLE_EOF) {
      SET_REQ_RESULT(req, bytes);
    } else {
      SET_REQ_WIN32_ERROR(req, error);
    }
  }
}