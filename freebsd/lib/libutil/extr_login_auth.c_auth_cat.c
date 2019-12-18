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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZ ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

int
auth_cat(const char *file)
{
  int fd, count;
  char buf[BUFSIZ];

  if ((fd = open(file, O_RDONLY | O_CLOEXEC)) < 0)
    return 0;
  while ((count = read(fd, buf, sizeof(buf))) > 0)
    (void)write(fileno(stdout), buf, count);
  close(fd);
  sleep(5);	/* wait an arbitrary time to drain */
  return 1;
}