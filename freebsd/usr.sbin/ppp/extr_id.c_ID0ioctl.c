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
 int /*<<< orphan*/  ID0set0 () ; 
 int /*<<< orphan*/  ID0setuser () ; 
 int /*<<< orphan*/  LogID0 ; 
 int ioctl (int,unsigned long,void*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,int,unsigned long,void*) ; 

int
ID0ioctl(int fd, unsigned long req, void *arg)
{
  int ret;

  ID0set0();
  ret = ioctl(fd, req, arg);
  log_Printf(LogID0, "%d = ioctl(%d, %lu, %p)\n", ret, fd, req, arg);
  ID0setuser();
  return ret;
}