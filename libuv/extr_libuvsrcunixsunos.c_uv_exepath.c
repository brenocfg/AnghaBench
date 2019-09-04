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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int UV_EINVAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpid () ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 

int uv_exepath(char* buffer, size_t* size) {
  ssize_t res;
  char buf[128];

  if (buffer == NULL || size == NULL || *size == 0)
    return UV_EINVAL;

  snprintf(buf, sizeof(buf), "/proc/%lu/path/a.out", (unsigned long) getpid());

  res = *size - 1;
  if (res > 0)
    res = readlink(buf, buffer, res);

  if (res == -1)
    return UV__ERR(errno);

  buffer[res] = '\0';
  *size = res;
  return 0;
}