#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dir_handle; int /*<<< orphan*/ * dirw; int /*<<< orphan*/ * path; int /*<<< orphan*/ * short_filew; int /*<<< orphan*/ * filew; } ;
typedef  TYPE_1__ uv_fs_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__is_active (TYPE_1__*) ; 

int uv_fs_event_stop(uv_fs_event_t* handle) {
  if (!uv__is_active(handle))
    return 0;

  if (handle->dir_handle != INVALID_HANDLE_VALUE) {
    CloseHandle(handle->dir_handle);
    handle->dir_handle = INVALID_HANDLE_VALUE;
  }

  uv__handle_stop(handle);

  if (handle->filew) {
    uv__free(handle->filew);
    handle->filew = NULL;
  }

  if (handle->short_filew) {
    uv__free(handle->short_filew);
    handle->short_filew = NULL;
  }

  if (handle->path) {
    uv__free(handle->path);
    handle->path = NULL;
  }

  if (handle->dirw) {
    uv__free(handle->dirw);
    handle->dirw = NULL;
  }

  return 0;
}