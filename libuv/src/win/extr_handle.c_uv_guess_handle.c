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
typedef  int /*<<< orphan*/  uv_handle_type ;
typedef  scalar_t__ uv_file ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
#define  FILE_TYPE_CHAR 130 
#define  FILE_TYPE_DISK 129 
#define  FILE_TYPE_PIPE 128 
 int /*<<< orphan*/  GetConsoleMode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetFileType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV_FILE ; 
 int /*<<< orphan*/  UV_NAMED_PIPE ; 
 int /*<<< orphan*/  UV_TTY ; 
 int /*<<< orphan*/  UV_UNKNOWN_HANDLE ; 
 int /*<<< orphan*/  uv__get_osfhandle (scalar_t__) ; 

uv_handle_type uv_guess_handle(uv_file file) {
  HANDLE handle;
  DWORD mode;

  if (file < 0) {
    return UV_UNKNOWN_HANDLE;
  }

  handle = uv__get_osfhandle(file);

  switch (GetFileType(handle)) {
    case FILE_TYPE_CHAR:
      if (GetConsoleMode(handle, &mode)) {
        return UV_TTY;
      } else {
        return UV_FILE;
      }

    case FILE_TYPE_PIPE:
      return UV_NAMED_PIPE;

    case FILE_TYPE_DISK:
      return UV_FILE;

    default:
      return UV_UNKNOWN_HANDLE;
  }
}