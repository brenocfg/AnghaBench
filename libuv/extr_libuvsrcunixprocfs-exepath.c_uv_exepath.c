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
typedef  int ssize_t ;

/* Variables and functions */
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int readlink (char*,char*,int) ; 

int uv_exepath(char* buffer, size_t* size) {
  ssize_t n;

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  n = *size - 1;
  if (n > 0)
    n = readlink("/proc/self/exe", buffer, n);

  if (n == -1)
    return UV__ERR(errno);

  buffer[n] = '\0';
  *size = n;

  return 0;
}