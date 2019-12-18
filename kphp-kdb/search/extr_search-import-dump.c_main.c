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
 int /*<<< orphan*/  Args_per_line ; 
 int /*<<< orphan*/  Map ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEARCH_SCHEMA_V1 ; 
#define  TF_APPS 138 
#define  TF_AUDIO 137 
#define  TF_BLOG_POSTS 136 
#define  TF_EVENTS 135 
#define  TF_GROUPS 134 
#define  TF_MARKET_ITEMS 133 
#define  TF_MEMLITE 132 
#define  TF_MINIFEED 131 
#define  TF_QUESTIONS 130 
#define  TF_TOPICS 129 
#define  TF_VIDEO 128 
 int /*<<< orphan*/  ap_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atol (char*) ; 
 int /*<<< orphan*/  au_END ; 
 int /*<<< orphan*/  bp_END ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fdatasync (int) ; 
 int /*<<< orphan*/  flush_out () ; 
 char* fname_last (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_dump_format (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  gr_END ; 
 char* groups_fname ; 
 int /*<<< orphan*/  load_map (int) ; 
 scalar_t__ map_changes ; 
 int map_fd ; 
 int map_size ; 
 int /*<<< orphan*/  mf_END ; 
 int /*<<< orphan*/  mi_END ; 
 int /*<<< orphan*/  ml_END ; 
 void* open (char*,int,...) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  output_format ; 
 int /*<<< orphan*/  output_stats () ; 
 int /*<<< orphan*/  process_applications_row () ; 
 int /*<<< orphan*/  process_audio_row () ; 
 int /*<<< orphan*/  process_blog_posts_row () ; 
 int /*<<< orphan*/  process_events_row () ; 
 int /*<<< orphan*/  process_groups_row () ; 
 int /*<<< orphan*/  process_market_row () ; 
 int /*<<< orphan*/  process_memlite_row () ; 
 int /*<<< orphan*/  process_minifeed_row () ; 
 int /*<<< orphan*/  process_questions_row () ; 
 int /*<<< orphan*/  process_topics_row () ; 
 int /*<<< orphan*/  process_video_row () ; 
 char* progname ; 
 int /*<<< orphan*/  qu_END ; 
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
 int /*<<< orphan*/  to_END ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vi_END ; 
 int write (int,int /*<<< orphan*/ ,int) ; 

int main (int argc, char *argv[]) {
  int i;
  progname = argv[0];
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
    case 'g':
      groups_fname = optarg;
      break;
    case 'o':
      output_format = atol (optarg);
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
  case TF_AUDIO:
    Args_per_line = au_END;
    start_binlog(SEARCH_SCHEMA_V1, "audio_search");
    while (read_record() > 0) {
      process_audio_row();
    }
    break;
  case TF_VIDEO:
    Args_per_line = vi_END;
    start_binlog(SEARCH_SCHEMA_V1, "video_search");
    while (read_record() > 0) {
      process_video_row();
    }
    break;
  case TF_APPS:
    Args_per_line = ap_END;
    start_binlog(SEARCH_SCHEMA_V1, "apps_search");
    while (read_record() > 0) {
      process_applications_row();
    }
    break;
  case TF_GROUPS:
    Args_per_line = gr_END;
    start_binlog(SEARCH_SCHEMA_V1, "group_search");
    while (read_record() > 0) {
      process_groups_row();
    }
    break;
  case TF_EVENTS:
    Args_per_line = gr_END;
    start_binlog(SEARCH_SCHEMA_V1, "event_search");
    while (read_record() > 0) {
      process_events_row();
    }
    break;
  case TF_BLOG_POSTS:
    Args_per_line = bp_END;
    start_binlog(SEARCH_SCHEMA_V1, "blog_posts_search");
    while (read_record() > 0) {
      process_blog_posts_row();
    }
    break;
  case TF_MEMLITE:
    Args_per_line = ml_END;
    start_binlog(SEARCH_SCHEMA_V1, "member_name_search");
    while (read_record() > 0) {
      process_memlite_row();
    }
    break;
  case TF_MARKET_ITEMS:
    Args_per_line = mi_END;
    start_binlog(SEARCH_SCHEMA_V1, "market_search");
    while (read_record() > 0) {
      process_market_row();
    }
    break;
  case TF_QUESTIONS:
    Args_per_line = qu_END;
    start_binlog(SEARCH_SCHEMA_V1, "question_search");
    while (read_record() > 0) {
      process_questions_row();
    }
    break;
  case TF_TOPICS:
    load_map (1);
    Args_per_line = to_END;
    start_binlog(SEARCH_SCHEMA_V1, "topic_search");
    while (read_record() > 0) {
      process_topics_row();
    }
    break;
  case TF_MINIFEED:
    Args_per_line = mf_END;
    start_binlog(SEARCH_SCHEMA_V1, "status_search");
    while (read_record() > 0) {
      process_minifeed_row();
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

  if (map_size > 0 && map_changes > 0 && groups_fname) {
    map_fd = open (groups_fname, O_WRONLY | O_CREAT | O_TRUNC, 0640);
    if (map_fd < 0) {
      fprintf (stderr, "cannot create map file %s: %m\n", groups_fname);
      exit (1);
    }
    assert (write (map_fd, Map, map_size) == map_size);
    close (map_fd);
    if (verbosity > 0) {
      fprintf (stderr, "%d bytes written to map file %s\n", map_size, groups_fname);
    }
  }

  if (verbosity > 0) {
    output_stats();
  }

  return 0;
}