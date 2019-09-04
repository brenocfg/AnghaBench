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
typedef  int /*<<< orphan*/  val ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int write (int,int*,int) ; 

__attribute__((used)) static void uv__write_int(int fd, int val) {
  ssize_t n;

  do
    n = write(fd, &val, sizeof(val));
  while (n == -1 && errno == EINTR);

  if (n == -1 && errno == EPIPE)
    return; /* parent process has quit */

  assert(n == sizeof(val));
}