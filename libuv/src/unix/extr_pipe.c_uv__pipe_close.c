#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pipe_fname; } ;
typedef  TYPE_1__ uv_pipe_t ;

/* Variables and functions */
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__free (void*) ; 
 int /*<<< orphan*/  uv__stream_close (int /*<<< orphan*/ *) ; 

void uv__pipe_close(uv_pipe_t* handle) {
  if (handle->pipe_fname) {
    /*
     * Unlink the file system entity before closing the file descriptor.
     * Doing it the other way around introduces a race where our process
     * unlinks a socket with the same name that's just been created by
     * another thread or process.
     */
    unlink(handle->pipe_fname);
    uv__free((void*)handle->pipe_fname);
    handle->pipe_fname = NULL;
  }

  uv__stream_close((uv_stream_t*)handle);
}