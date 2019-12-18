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
struct TYPE_3__ {int emfile_fd; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int UV_EINTR ; 
 int UV_EMFILE ; 
 int uv__accept (int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int uv__open_cloexec (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uv__emfile_trick(uv_loop_t* loop, int accept_fd) {
  int err;
  int emfile_fd;

  if (loop->emfile_fd == -1)
    return UV_EMFILE;

  uv__close(loop->emfile_fd);
  loop->emfile_fd = -1;

  do {
    err = uv__accept(accept_fd);
    if (err >= 0)
      uv__close(err);
  } while (err >= 0 || err == UV_EINTR);

  emfile_fd = uv__open_cloexec("/", O_RDONLY);
  if (emfile_fd >= 0)
    loop->emfile_fd = emfile_fd;

  return err;
}