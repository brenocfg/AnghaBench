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
 char** GP ; 
 int MAX_GROUP_PATHS ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ change_user (char*) ; 
 int dump_rows ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (void*,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  import_lev_start () ; 
 int /*<<< orphan*/  import_paths (char*,int) ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 void* optarg ; 
 int optind ; 
 scalar_t__ pmemcache_dump ; 
 char* progname ; 
 void* row_prefix ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int split_modulo ; 
 int split_rem ; 
 int sscanf (void*,char*,...) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  test_paths (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int use_old_secret ; 
 char* username ; 
 int /*<<< orphan*/  verbosity ; 
 scalar_t__ volume_id ; 

int main (int argc, char *argv[]) {
  int i;
  int dump_lev_start = 1;
  set_debug_handlers();
  progname = strrchr (argv[0], '/');
  progname = (progname == NULL) ? argv[0] : progname + 1;
  int group_paths = 0;
  while ((i = getopt (argc, argv, "m:vu:Ip:g:V:TP:S")) != -1) {
    switch (i) {
    case 'S':
      use_old_secret = 1;
      break;
    case 'P':
      if (pmemcache_dump) {
        fclose (pmemcache_dump);
      }
      pmemcache_dump = fopen (optarg, "a");
      break;
    case 'T':
      dump_lev_start = 0;
      break;
    case 'V':
      sscanf (optarg, "%lld", &volume_id);
      break;
    case 'm':
      assert (sscanf (optarg, "%d,%d", &split_rem, &split_modulo) == 2);
      assert (split_modulo > 0 && split_modulo <= 1000 && split_rem >= 0 && split_rem < split_modulo);
      break;
    case 'v':
      verbosity++;
      break;
    case 'u':
      username = optarg;
      break;
    case 'I':
      dump_rows = 1;
      break;
    case 'p':
      row_prefix = optarg;
      break;
    case 'g':
      assert (group_paths < MAX_GROUP_PATHS);
      GP[group_paths++] = optarg;
    }
  }

  if (volume_id < 0) {
    usage ();
    kprintf ("volume_id is not given\n");
    exit (1);
  }

  if (!split_modulo) {
    usage ();
    kprintf ("-m option is not given\n");
    exit (1);
  }

  if (10000 % split_modulo) {
    kprintf ("split_modulo should divides 10000\n");
    exit (1);
  }

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit(1);
  }

  for (i = optind; i < argc; i++) {
    test_paths (argv[i]);
  }
  for (i = 0; i < group_paths; i++) {
    test_paths (GP[i]);
  }

  init_dyn_data ();
  aes_load_pwd_file (NULL);
  if (dump_lev_start) {
    import_lev_start ();
  }

  for (i = optind; i < argc; i++) {
    import_paths (argv[i], 1);
  }
  for (i = 0; i < group_paths; i++) {
    import_paths (GP[i], -1);
  }
/*
  kprintf ("opened_base_doc = %d, opened_aux_doc = %d\n", opened_base_doc, opened_aux_doc);
  kprintf ("successfully_read_base_doc = %d, successfully_read_aux_doc = %d\n", successfully_read_base_doc, successfully_read_aux_doc);
*/
  if (pmemcache_dump) {
    fclose (pmemcache_dump);
  }

  return 0;
}