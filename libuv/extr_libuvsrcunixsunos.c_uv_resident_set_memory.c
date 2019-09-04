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
struct TYPE_3__ {scalar_t__ pr_rssize; } ;
typedef  TYPE_1__ psinfo_t ;
typedef  int /*<<< orphan*/  psinfo ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  uv__close (int) ; 

int uv_resident_set_memory(size_t* rss) {
  psinfo_t psinfo;
  int err;
  int fd;

  fd = open("/proc/self/psinfo", O_RDONLY);
  if (fd == -1)
    return UV__ERR(errno);

  /* FIXME(bnoordhuis) Handle EINTR. */
  err = UV_EINVAL;
  if (read(fd, &psinfo, sizeof(psinfo)) == sizeof(psinfo)) {
    *rss = (size_t)psinfo.pr_rssize * 1024;
    err = 0;
  }
  uv__close(fd);

  return err;
}