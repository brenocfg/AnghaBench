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
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int* fd ; 
 int /*<<< orphan*/  flush_w_buff () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_files (int) ; 
 int /*<<< orphan*/  open_file (int,char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 char* progname ; 
 int /*<<< orphan*/  run () ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 

int main (int argc, char *argv[]) {
  int i;

  set_debug_handlers ();
  progname = argv[0];

  if (argc == 1) {
    usage();
    return 2;
  }

  while ((i = getopt (argc, argv, "hu:")) != -1) {
    switch (i) {
    case 'h':
      usage ();
      return 2;
    case 'u':
      username = optarg;
      break;
    }
  }
  if (argc != optind + 2) {
    usage();
    return 2;
  }

  if (change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  init_files (3);

  open_file (0, argv[optind], 0);
  open_file (1, argv[optind + 1], 0);
  fd[2] = 1;

  run();

  flush_w_buff();
  fsync (fd[2]);
//  assert (fsync (fd[2]) >= 0);  // fails when stdout is a pipe

  return 0;
}