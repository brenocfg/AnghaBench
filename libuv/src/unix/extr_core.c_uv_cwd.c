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
typedef  int /*<<< orphan*/  scratch ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int UV_EINVAL ; 
 int UV_ENOBUFS ; 
 int UV__ERR (scalar_t__) ; 
 int /*<<< orphan*/  UV__PATH_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 size_t strlen (char*) ; 

int uv_cwd(char* buffer, size_t* size) {
  char scratch[1 + UV__PATH_MAX];

  if (buffer == NULL || size == NULL)
    return UV_EINVAL;

  /* Try to read directly into the user's buffer first... */
  if (getcwd(buffer, *size) != NULL)
    goto fixup;

  if (errno != ERANGE)
    return UV__ERR(errno);

  /* ...or into scratch space if the user's buffer is too small
   * so we can report how much space to provide on the next try.
   */
  if (getcwd(scratch, sizeof(scratch)) == NULL)
    return UV__ERR(errno);

  buffer = scratch;

fixup:

  *size = strlen(buffer);

  if (*size > 1 && buffer[*size - 1] == '/') {
    *size -= 1;
    buffer[*size] = '\0';
  }

  if (buffer == scratch) {
    *size += 1;
    return UV_ENOBUFS;
  }

  return 0;
}