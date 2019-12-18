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
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* logname ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void reopen_logs (void) {
  int fd;

  fflush (stdout);
  fflush (stderr);

  if ((fd = open ("/dev/null", O_RDWR, 0)) != -1) {
    dup2 (fd, 0);
    dup2 (fd, 1);
    dup2 (fd, 2);
    if (fd > 2) {
      close (fd);
    }
  }
  if (logname && (fd = open (logname, O_WRONLY|O_APPEND|O_CREAT, 0640)) != -1) {
    dup2 (fd, 1);
    dup2 (fd, 2);
    if (fd > 2) {
      close (fd);
    }
  }
}