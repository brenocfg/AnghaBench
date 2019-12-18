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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  icpl_init () ; 
 scalar_t__ icpl_parse (char*) ; 
 char* icpl_readfile (char*) ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 int optind ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbosity ; 

int main (int argc, char *argv[]) {
  int i;
  set_debug_handlers ();
  while ((i = getopt (argc, argv, "hv")) != -1) {
    switch (i) {
    case 'h':
      usage ();
      return 2;
    case 'v':
      verbosity++;
      break;
    }
  }

  if (argc != optind + 1) {
    usage ();
  }
  
  char *prog_filename = argv[optind];

  init_dyn_data ();
  icpl_init ();
  char *a = icpl_readfile (prog_filename);
  if (a == NULL) {
    kprintf ("icpl_readfile (\"%s\") fail.\n", prog_filename);
    exit (1);
  }

  if (icpl_parse (a) < 0) {
    free (a);
    exit (1);
  }

  free (a);
  return 0;
}