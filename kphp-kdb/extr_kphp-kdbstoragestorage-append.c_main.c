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
 int /*<<< orphan*/  atoi (char*) ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exit_on_file_body_error ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  http_port ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 int memory_repairing ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  storage_binlog_append (char*,char*) ; 
 scalar_t__ storage_memory_repair (char*,char*) ; 
 int test_mode ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 int /*<<< orphan*/  verbosity ; 

int main (int argc, char *argv[]) {
  int i;
  while ((i = getopt (argc, argv, "1H:mtuv")) != -1) {
    switch (i) {
      case 'H':
        http_port = atoi (optarg);
      break;
      case 'm':
        memory_repairing = 1;
      break;
      case 't':
        test_mode = 1;
      break;
      case 'u':
        username = optarg;
      break;
      case 'v':
        verbosity++;
        break;
      case '1':
        exit_on_file_body_error = 0;
        break;
    }
  }
  if (argc < optind + 2) {
    usage ();
    return 1;
  }

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  if (memory_repairing) {
    if (storage_memory_repair (argv[optind], argv[optind+1]) < 0) {
      unlink (argv[optind+1]);
      return 1;
    }
    return 0;
  }

  storage_binlog_append (argv[optind], argv[optind+1]);
  return 0;
}