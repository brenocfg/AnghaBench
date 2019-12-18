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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EINTR ; 
 int S_BUF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kwrite_print_int (char**,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ write (int,void const*,size_t) ; 

ssize_t kwrite (int fd, const void *buf, size_t count) {
  int old_errno = errno;

#define S_BUF_SIZE 100
  char s[S_BUF_SIZE], *s_begin = s + S_BUF_SIZE;

  kwrite_print_int (&s_begin, "time", 4, time (NULL));
  kwrite_print_int (&s_begin, "pid" , 3, getpid ());

  assert (s_begin >= s);

  size_t s_count = s + S_BUF_SIZE - s_begin;
  ssize_t result = s_count + count;
  while (s_count > 0) {
    errno = 0;
    ssize_t res = write (fd, s_begin, s_count);
    if (errno && errno != EINTR) {
      errno = old_errno;
      return res;
    }
    if (!res) {
      break;
    }
    if (res >= 0) {
      s_begin += res;
      s_count -= res;
    }
  }

  while (count > 0) {
    errno = 0;
    ssize_t res = write (fd, buf, count);
    if (errno && errno != EINTR) {
      errno = old_errno;
      return res;
    }
    if (!res) {
      break;
    }
    if (res >= 0) {
      buf += res;
      count -= res;
    }
  }

  errno = old_errno;
  return result;
#undef S_BUF_SIZE
}