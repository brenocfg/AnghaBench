#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ EISDIR ; 
 scalar_t__ ENOENT ; 
 int MAX_FPATH_LEN ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_remove_pidfile ; 
 char* dstdir ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int getpid () ; 
 int /*<<< orphan*/  kprintf (char*,char*,...) ; 
 int open (char*,int,...) ; 
 char* pidfile ; 
 int pidfile_created ; 
 int read (int,char*,int) ; 
 int sprintf (char*,char*,...) ; 
 scalar_t__ stat (char*,TYPE_1__*) ; 
 TYPE_1__ tmp_stat ; 
 scalar_t__ unlink (char*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int create_pidfile (void) {
  static char tmp_buff[32];
  int old_pid, fd;

  assert (sprintf (pidfile, "%s/backup.pid", dstdir) < MAX_FPATH_LEN);

  if (stat (pidfile, &tmp_stat) >= 0) {
    if (!S_ISREG (tmp_stat.st_mode)) {
      errno = EISDIR;
      return -1;
    }
    int fd = open (pidfile, O_RDONLY);
    if (fd < 0) {
      return -1;
    }
    int r = read (fd, tmp_buff, 16);
    close (fd);
    if (r < 0) {
      return -1;
    }
    if (r < 16) {
      tmp_buff[r] = 0;
      old_pid = atoi (tmp_buff);
      if (old_pid > 0) {
        sprintf (tmp_buff, "/proc/%d/", old_pid);
        if (stat (tmp_buff, &tmp_stat) >= 0) {
          kprintf ("fatal: destination directory %s already locked by process %d\n", dstdir, old_pid);
          exit (2);
        }
      }
    }
    kprintf ("warning: removing stale pid file %s\n", pidfile);
    if (unlink (pidfile) < 0 && errno != ENOENT) {
      return -1;
    }
  }

  fd = open (pidfile, O_WRONLY | O_CREAT | O_EXCL, 0640);
  if (fd < 0) {
    return -1;
  }

  pidfile_created = 1;
  atexit (do_remove_pidfile);	/* think about this */

  int s = sprintf (tmp_buff, "%d\n", getpid());
  if (write (fd, tmp_buff, s) != s) {
    close (fd);
    return -1;
  }
  close (fd);
  return 0;
}