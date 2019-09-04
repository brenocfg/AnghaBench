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
 size_t ARRAY_SIZE (char*) ; 
 int CTL_KERN ; 
 int KERN_PROC_ARGS ; 
 int KERN_PROC_PATHNAME ; 
 int PATH_MAX ; 
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 size_t strlen (char*) ; 
 scalar_t__ sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__strscpy (char*,char*,size_t) ; 

int uv_exepath(char* buffer, size_t* size) {
  /* Intermediate buffer, retrieving partial path name does not work
   * As of NetBSD-8(beta), vnode->path translator does not handle files
   * with longer names than 31 characters.
   */
  char int_buf[PATH_MAX];
  size_t int_size;
  int mib[4];

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC_ARGS;
  mib[2] = -1;
  mib[3] = KERN_PROC_PATHNAME;
  int_size = ARRAY_SIZE(int_buf);

  if (sysctl(mib, 4, int_buf, &int_size, NULL, 0))
    return UV__ERR(errno);

  /* Copy string from the intermediate buffer to outer one with appropriate
   * length.
   */
  /* TODO(bnoordhuis) Check uv__strscpy() return value. */
  uv__strscpy(buffer, int_buf, *size);

  /* Set new size. */
  *size = strlen(buffer);

  return 0;
}