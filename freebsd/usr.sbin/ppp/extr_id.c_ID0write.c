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
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,int,long) ; 
 int write (int,void const*,size_t) ; 

int
ID0write(int fd, const void *data, size_t len)
{
  int ret;

  ID0set0();
  ret = write(fd, data, len);
  log_Printf(LogID0, "%d = write(%d, data, %ld)\n", ret, fd, (long)len);
  ID0setuser();
  return ret;
}