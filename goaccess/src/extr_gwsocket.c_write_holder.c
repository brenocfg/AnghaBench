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
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int write (int,char const*,int) ; 

__attribute__((used)) static int
write_holder (int fd, const char *buf, int len)
{
  int i, ret = 0;

  for (i = 0; i < len;) {
    ret = write (fd, buf + i, len - i);
    if (ret < 0) {
      if (errno == EINTR || errno == EAGAIN)
        continue;
      return -1;
    } else {
      i += ret;
    }
  }

  return i;
}