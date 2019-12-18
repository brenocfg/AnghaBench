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
 int MAX_FN ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  dl_strdup (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int* fd ; 
 int /*<<< orphan*/ * fnames ; 
 scalar_t__* fpos ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int* fread_only ; 
 int /*<<< orphan*/ * fsize ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char const*,int,int) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int dl_open_file (int x, const char *fname, int creat) {
  if (x < 0 || x >= MAX_FN) {
    fprintf (stderr, "%s: cannot open %s, bad local fid %d: %m\n", progname, fname, x);
    return -1;
  }

  fnames[x] = dl_strdup (fname);
  int options;
  if (creat > 0) {
    options = O_RDWR | O_CREAT;
    if (creat == 2) {
      options |= O_TRUNC;
    }
  } else {
    fread_only[x] = 1;
    options = O_RDONLY;
  }

  fd[x] = open (fname, options, 0600);
  if (creat < 0 && fd[x] < 0) {
    fprintf (stderr, "%s: cannot open %s: %m\n", progname, fname);
    return -1;
  }
  if (fd[x] < 0) {
    fprintf (stderr, "%s: cannot open %s: %m\n", progname, fname);
    exit (1);
  }
  fsize[x] = lseek (fd[x], 0, SEEK_END);
  if (fsize[x] < 0) {
    fprintf (stderr, "%s: cannot seek %s: %m\n", progname, fname);
    exit (2);
  }
  lseek (fd[x], 0, SEEK_SET);
  if (verbosity) {
    fprintf (stderr, "opened file %s, fd=%d, size=%lld\n", fname, fd[x], fsize[x]);
  }
  fpos[x] = 0;
  return fd[x];
}