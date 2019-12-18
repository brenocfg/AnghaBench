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
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  WB ; 
 int /*<<< orphan*/  WRITE_BUFFER_SIZE ; 
 int addr_ext_size ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int curr_fd ; 
 char* curr_fname ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fdatasync (int) ; 
 int /*<<< orphan*/  flush_out () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int mode ; 
 void* open (char*,int,...) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  output_stats () ; 
 scalar_t__ position ; 
 scalar_t__ process_record () ; 
 char* progname ; 
 int read (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rend ; 
 scalar_t__ rptr ; 
 scalar_t__ src_fd ; 
 char* src_fname ; 
 int /*<<< orphan*/  stderr ; 
 int targ_fd ; 
 char* targ_fname ; 
 scalar_t__ targ_orig_size ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 
 int time_offset ; 
 scalar_t__ time_threshold ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 scalar_t__ verbosity ; 
 int write (int,int /*<<< orphan*/ ,int) ; 

int main (int argc, char *argv[]) {
  int i;
  progname = argv[0];
  while ((i = getopt (argc, argv, "hviu:t:")) != -1) {
    switch (i) {
    case 'v':
      verbosity = 1;
      break;
    case 'h':
      usage();
      return 2;
    case 'u':
      username = optarg;
      break;
    case 't':
      time_offset = atoi (optarg);
      break;
    case 'i':
      addr_ext_size = 29;
      break;
    }
  }

  if (optind >= argc || optind + 3 < argc) {
    usage();
    return 2;
  }

  if (time_offset <= 0) {
    time_offset = 86400;
  }
  time_threshold = time(0) - time_offset;

  src_fname = argv[optind];

  if (username && change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    return 1;
  }

  src_fd = open (src_fname, O_RDONLY);
  if (src_fd < 0) {
    fprintf (stderr, "cannot open %s: %m\n", src_fname);
    return 1;
  }

  if (optind + 2 < argc) {
    curr_fname = argv[optind+2];
    curr_fd = open (curr_fname, O_RDONLY);
    mode = 1;
    if (curr_fd < 0) {
      fprintf (stderr, "cannot open %s: %m\n", curr_fname);
      return 1;
    }
  }

  if (optind + 1 < argc) {
    targ_fname = argv[optind+1];
    targ_fd = open (targ_fname, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (targ_fd < 0) {
      fprintf (stderr, "cannot create %s: %m\n", targ_fname);
      return 1;
    }
    targ_orig_size = lseek (targ_fd, 0, SEEK_END);
    assert (targ_orig_size > 0);
  } else {
    targ_fname = "stdout";
    targ_fd = 1;
  }

  while (process_record() >= 0) { }

  flush_out();

  if (mode == 2 && rend == rptr) {
    assert (position > 0);
    position += targ_orig_size;
    if (verbosity > 0) {
      fprintf (stderr, "copying from position %lld of file %s\n", position, curr_fname);
    }
    assert (lseek (curr_fd, position, SEEK_SET) == position);
    while (1) {
      int r = read (curr_fd, WB, WRITE_BUFFER_SIZE);
      if (r <= 0) { assert (!r); break; }
      int w = write (targ_fd, WB, r);
      assert (w == r);
    }
    if (verbosity > 0) {
      fprintf (stderr, "transferred %lld bytes from %s\n", lseek(curr_fd, 0, SEEK_CUR) - position, curr_fname);
    }
  }

  if (targ_fd != 1) {
    if (fdatasync(targ_fd) < 0) {
      fprintf (stderr, "error syncing %s: %m", targ_fname);
      exit (1);
    }
    close (targ_fd);
  }

  if (verbosity > 0) {
    output_stats();
  }

  return rend > rptr ? 1 : 0;
}