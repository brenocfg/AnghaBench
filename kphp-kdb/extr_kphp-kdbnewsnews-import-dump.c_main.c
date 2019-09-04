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
 int /*<<< orphan*/  SPLIT_PARAM_OWNER ; 
 int /*<<< orphan*/  SPLIT_PARAM_OWNERXPLACE ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  import_dump () ; 
 int /*<<< orphan*/  import_dump2 () ; 
 int /*<<< orphan*/  import_file ; 
 int /*<<< orphan*/  log_split_mod ; 
 char* name_pattern ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 char* progname ; 
 int /*<<< orphan*/  split_param ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbosity ; 

int main (int argc, char *argv[]) {
  progname = argv[0];
  int i;
  int mode = 0;
  while ((i = getopt (argc, argv, "m:vn:oxz")) != -1) {
    switch (i) {
    case 'v':
      verbosity++;
      break;
    case 'm':
      log_split_mod = atoi (optarg);
      break;
    case 'n':
      import_file = optarg;
      break;
    case 'o':
      split_param = SPLIT_PARAM_OWNER;
      break;
    case 'x':
      split_param = SPLIT_PARAM_OWNERXPLACE;
      break;
    case 'z':
      mode = 1;
      break;
    case 'h':
    default:
      usage ();
      return 2;
    }
  }
  if (argc != optind + 1 || !import_file || !log_split_mod) {
    usage();
    return 2;
  }
  name_pattern = argv[optind];
  if (mode == 0) {
    import_dump ();
  } else {
    import_dump2 ();
  }
  return 0;
}