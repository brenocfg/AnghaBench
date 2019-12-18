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

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PROC ; 
 int KERN_PROC_PATHNAME ; 
 int PATH_MAX ; 
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_exepath(char* buffer, size_t* size) {
  char abspath[PATH_MAX * 2 + 1];
  int mib[4];
  size_t abspath_size;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PATHNAME;
  mib[3] = -1;

  abspath_size = sizeof abspath;
  if (sysctl(mib, 4, abspath, &abspath_size, NULL, 0))
    return UV__ERR(errno);

  assert(abspath_size > 0);
  abspath_size -= 1;
  *size -= 1;

  if (*size > abspath_size)
    *size = abspath_size;

  memcpy(buffer, abspath, *size);
  buffer[*size] = '\0';

  return 0;
}