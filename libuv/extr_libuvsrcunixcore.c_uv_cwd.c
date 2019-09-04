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
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * getcwd (char*,size_t) ; 
 size_t strlen (char*) ; 

int uv_cwd(char* buffer, size_t* size) {
  if (buffer == NULL || size == NULL)
    return UV_EINVAL;

  if (getcwd(buffer, *size) == NULL)
    return UV__ERR(errno);

  *size = strlen(buffer);
  if (*size > 1 && buffer[*size - 1] == '/') {
    buffer[*size-1] = '\0';
    (*size)--;
  }

  return 0;
}