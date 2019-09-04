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
typedef  unsigned long uint64_t ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  abort () ; 
 size_t read (int,char*,int) ; 
 int sscanf (char*,char*,unsigned long*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char*,char const*) ; 
 scalar_t__ uv__close_nocheckstdio (int) ; 
 int uv__open_cloexec (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t uv__read_proc_meminfo(const char* what) {
  unsigned long rc;
  ssize_t n;
  char* p;
  int fd;
  char buf[4096];  /* Large enough to hold all of /proc/meminfo. */

  rc = 0;
  fd = uv__open_cloexec("/proc/meminfo", O_RDONLY);

  if (fd == -1)
    return 0;

  n = read(fd, buf, sizeof(buf) - 1);

  if (n <= 0)
    goto out;

  buf[n] = '\0';
  p = strstr(buf, what);

  if (p == NULL)
    goto out;

  p += strlen(what);

  if (1 != sscanf(p, "%lu kB", &rc))
    goto out;

  rc *= 1024;

out:

  if (uv__close_nocheckstdio(fd))
    abort();

  return rc;
}