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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int atoi (scalar_t__) ; 
 int /*<<< orphan*/  buff ; 
 int /*<<< orphan*/  dump (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fgets (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  freopen (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  init () ; 
 scalar_t__ input_file ; 
 int mode ; 
 scalar_t__ optarg ; 
 int optind ; 
 scalar_t__ output_file ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  run () ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int total_out ; 
 scalar_t__ verbosity ; 

int main (int argc, char **argv) {
  int i;
  int skip_lines = 0;
  set_debug_handlers ();

  while ((i = getopt (argc, argv, "i:o:vhs:m")) != -1) {
    switch (i) {
    case 'v':
      verbosity++;
      break;
    case 'h':
      help();
      return 2;
    case 'i':
      input_file = optarg;
      break;
    case 'o':
      output_file = optarg;
      break;
    case 's':
      skip_lines = atoi (optarg);
      break;
    case 'm':
      mode ++;
      break;
    default:
      help ();
      return 2;
    }
  }

  if (argc != optind || !input_file) {
    help();
    return 2;
  }

  if (output_file) {
    assert (freopen (output_file, "wt", stdout));
  }

  printf ("%d\n", mode);
  assert (freopen (input_file, "rt", stdin));
  for (i = 0; i < skip_lines; i++) {
    assert (fgets (buff, 1000000, stdin));
  }
  
  init ();
  run ();
  dump (&root, -1);
  if (verbosity) {
    fprintf (stderr, "Total %d rules\n", total_out);
  }

  return 0;
}