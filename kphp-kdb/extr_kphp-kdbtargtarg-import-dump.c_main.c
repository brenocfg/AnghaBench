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
 int Args_per_line ; 
 scalar_t__ GA ; 
 scalar_t__ GB ; 
 scalar_t__ GC ; 
 scalar_t__ GT ; 
 int Gc ; 
 int Gd ; 
 int /*<<< orphan*/  MAX_CHARS ; 
 int MAX_GID ; 
 int MAX_GROUPS ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  TARG_SCHEMA_V1 ; 
#define  TF_ADDRESSES 137 
#define  TF_EDUCATION 136 
#define  TF_GROUPSHORT 135 
#define  TF_MATCHES 134 
#define  TF_MEMEXTRA 133 
#define  TF_MEMGROUPS 132 
#define  TF_MEMLITE 131 
#define  TF_MEMSHORT 130 
#define  TF_MILITARY 129 
#define  TF_NAMES 128 
 int TS ; 
 int /*<<< orphan*/  Tc ; 
 int Tw ; 
 int /*<<< orphan*/  assert (int) ; 
 int atol (char*) ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fdatasync (int) ; 
 int /*<<< orphan*/  flush_memgroups () ; 
 int /*<<< orphan*/  flush_out () ; 
 int /*<<< orphan*/  flush_words () ; 
 char* fname_last (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_dump_format (char*) ; 
 int getopt (int,char**,char*) ; 
 char* groups_fname ; 
 char* groups_fname2 ; 
 int /*<<< orphan*/  init_allowed () ; 
 int malloc (int /*<<< orphan*/ ) ; 
 int mp_END ; 
 int ms_END ; 
 scalar_t__ open (char*,int,...) ; 
 char* optarg ; 
 int optind ; 
 int output_format ; 
 int /*<<< orphan*/  output_stats () ; 
 int /*<<< orphan*/  process_addresses_row () ; 
 int /*<<< orphan*/  process_education_row () ; 
 int /*<<< orphan*/  process_groupshort_row () ; 
 int /*<<< orphan*/  process_matches_row () ; 
 int /*<<< orphan*/  process_memextra_row () ; 
 int /*<<< orphan*/  process_memgroups_row () ; 
 int /*<<< orphan*/  process_memlite_row () ; 
 int /*<<< orphan*/  process_memshort_row () ; 
 int /*<<< orphan*/  process_military_row () ; 
 int /*<<< orphan*/  process_names_row () ; 
 char* progname ; 
 int read (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  read_record () ; 
 int split_mod ; 
 int split_rem ; 
 scalar_t__ src_fd ; 
 char* src_fname ; 
 int sscanf (char*,char*,int*,int*) ; 
 int /*<<< orphan*/  start_binlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int table_format ; 
 int targ_fd ; 
 char* targ_fname ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 scalar_t__ verbosity ; 
 int write (int,scalar_t__,int) ; 

int main (int argc, char *argv[]) {
  int i;
  progname = argv[0];
  init_allowed();
  while ((i = getopt (argc, argv, "hvu:m:f:g:o:")) != -1) {
    switch (i) {
    case 'v':
      verbosity = 1;
      break;
    case 'h':
      usage();
      return 2;
    case 'm':
      assert (sscanf(optarg, "%d,%d", &split_rem, &split_mod) == 2);
      assert (split_mod > 0 && split_mod <= 1000 && split_rem >= 0 && split_rem < split_mod);
      break;
    case 'f':
      table_format = get_dump_format(optarg);
      if (!table_format) {
	fprintf (stderr, "fatal: unsupported table dump format: %s\n", optarg);
	return 2;
      }
      break;
    case 'o':
      output_format = atol (optarg);
      break;
    case 'g':
      if (groups_fname) {
        groups_fname2 = optarg;
      } else {
        groups_fname = optarg;
      }
      break;
    case 'u':
      username = optarg;
      break;
    }
  }

  if (optind >= argc || optind + 2 < argc) {
    usage();
    return 2;
  }

  src_fname = argv[optind];

  if (username && change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    return 1;
  }

  if (groups_fname) {
    src_fd = open (groups_fname, O_RDONLY);
    if (src_fd < 0) {
      fprintf (stderr, "cannot open %s: %m\n", groups_fname);
      return 1;
    }
    Gc = read (src_fd, GT, MAX_GROUPS);
    if (verbosity > 0) {
      fprintf (stderr, "read %d bytes from %s\n", Gc, groups_fname);
    }
    assert (Gc >= 0 && Gc < MAX_GROUPS);
    close (src_fd);
    src_fd = 0;
    GA = GT;
    GC = GB = GA + ((Gc + 3) & -4);
  }

  if (groups_fname2) {
    src_fd = open (groups_fname2, O_RDONLY);
    if (src_fd < 0) {
      fprintf (stderr, "cannot open %s: %m\n", groups_fname2);
      return 1;
    }
    Gd = read (src_fd, GB, GA + MAX_GROUPS - GB);
    if (verbosity > 0) {
      fprintf (stderr, "read %d bytes from %s\n", Gd, groups_fname2);
    }
    assert (Gd >= 0 && Gd < MAX_GROUPS);
    close (src_fd);
    src_fd = 0;
    GC = GB + ((Gd + 3) & -4);
  }

  src_fd = open (src_fname, O_RDONLY);
  if (src_fd < 0) {
    fprintf (stderr, "cannot open %s: %m\n", src_fname);
    return 1;
  }

  if (!table_format) {
    table_format = get_dump_format (fname_last (src_fname));
    if (!table_format) {
      fprintf (stderr, "fatal: cannot determine table type from filename %s\n", src_fname);
    }
  }

  if (optind + 1 < argc) {
    targ_fname = argv[optind+1];
    targ_fd = open (targ_fname, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (targ_fd < 0) {
      fprintf (stderr, "cannot create %s: %m\n", targ_fname);
      return 1;
    }
  } else {
    targ_fname = "stdout";
    targ_fd = 1;
  }

  switch (table_format) {
  case TF_MEMLITE:
    Args_per_line = 27;
    start_binlog(TARG_SCHEMA_V1, "");
    while (read_record() > 0) {
      process_memlite_row();
    }
    break;
  case TF_EDUCATION:
    Args_per_line = 11;
    start_binlog(TARG_SCHEMA_V1, "");
    while (read_record() > 0) {
      process_education_row();
    }
    break;
  case TF_MEMSHORT:
    Args_per_line = ms_END;
    start_binlog(TARG_SCHEMA_V1, "");
    while (read_record() > 0) {
      process_memshort_row();
    }
    break;
  case TF_MEMEXTRA:
    Args_per_line = 3;
    if (output_format != 1) {
      start_binlog(TARG_SCHEMA_V1, "");
    }
    Tw = TS = malloc (MAX_CHARS);
    assert (TS);
    while (read_record() > 0) {
      process_memextra_row();
    }
    if (Tc) { flush_words(); }
    break;
  case TF_ADDRESSES:
    Args_per_line = 15;
    start_binlog(TARG_SCHEMA_V1, "");
    while (read_record() > 0) {
      process_addresses_row();
    }
    break;
  case TF_GROUPSHORT:
    Args_per_line = 3;
    while (read_record() > 0) {
      process_groupshort_row();
    }
    if (output_format == 1 && Gc) {
      assert (write (targ_fd, GT, Gc) == Gc);
    }
    break;
  case TF_MEMGROUPS:
    assert (Gc > 0);
    Args_per_line = 5;
    start_binlog(TARG_SCHEMA_V1, "");
    while (read_record() > 0) {
      process_memgroups_row();
    }
    flush_memgroups ();
    break;
  case TF_MILITARY:
    Args_per_line = 6;
    start_binlog(TARG_SCHEMA_V1, "");
    while (read_record() > 0) {
      process_military_row();
    }
    break;
  case TF_NAMES:
    Args_per_line = 2;
    Gc = MAX_GID * 4;
    while (read_record() > 0) {
      process_names_row();
    }
    if (output_format == 1 && Gc) {
      assert (write (targ_fd, GT, Gc) == Gc);
    }
    break;
  case TF_MATCHES:
    Args_per_line = mp_END;
    start_binlog(TARG_SCHEMA_V1, "");
    while (read_record() > 0) {
      process_matches_row();
    }
    break;
  default:
    fprintf (stderr, "unknown table type\n");
    exit(1);
  }

  flush_out();
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

  return 0;
}