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
 int MAX_CONNECTIONS ; 
 int atoi (char*) ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fix_rotate_to (char*,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int maxconn ; 
 char* optarg ; 
 int optind ; 
 scalar_t__ raise_file_rlimit (int) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 int /*<<< orphan*/  verbosity ; 

int main (int argc, char *argv[]) {
  int i;
  static int keep_bad_dest_file = 0;
  if (getuid ()) {
    maxconn = 10;
  }
  set_debug_handlers ();
  while ((i = getopt (argc, argv, "c:hku:v")) != -1) {
    switch (i) {
    case 'c':
      maxconn = atoi (optarg);
      if (maxconn <= 0 || maxconn > MAX_CONNECTIONS) {
      	maxconn = MAX_CONNECTIONS;
      }
    break;
    case 'h':
      usage ();
    break;
    case 'k':
      keep_bad_dest_file = 1;
      break;
    case 'u':
      username = optarg;
    break;
    case 'v':
      verbosity++;
    break;
    default:
      fprintf (stderr, "Unimplemented option %c\n", i);
      exit (2);
    break;
    }
  }

  if (optind + 3 != argc) {
    usage ();
  }

  if (raise_file_rlimit (maxconn + 16) < 0) {
    kprintf ("fatal: cannot raise open file limit to %d\n", maxconn + 16);
    exit (1);
  }

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  if (fix_rotate_to (argv[optind], argv[optind+1], argv[optind+2]) < 0) {
    if (!keep_bad_dest_file) {
      if (!unlink (argv[optind+2])) {
        kprintf ("Bad destination file '%s' was succesfully deleted.\n", argv[optind+2]);
      }
    }
    return 1;
  }

  return 0;
}