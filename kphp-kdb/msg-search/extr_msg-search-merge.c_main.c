#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  userlist_entry_t ;
struct TYPE_6__ {int user_id; scalar_t__ list_cnt; scalar_t__ hash_cnt; int /*<<< orphan*/  magic; } ;
struct TYPE_5__ {int delmsg_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ CurH ; 
 scalar_t__ CurL ; 
 int DEFAULT_CUTOFF_SECONDS ; 
 int /*<<< orphan*/  FILE_BUFFER_SIZE ; 
 int /*<<< orphan*/  MAIL_INDEX_BLOCK_MAGIC ; 
 unsigned int MAX_USER_ID ; 
 int M_cnt ; 
 int /*<<< orphan*/ * MetaB ; 
 int /*<<< orphan*/ ** MetaP ; 
 int PRIME ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_4__ User ; 
 TYPE_1__* UserMod ; 
 TYPE_1__** UserModHeaders ; 
 int* Users ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (void*) ; 
 scalar_t__ binlog_load_time ; 
 scalar_t__ binlog_loaded_size ; 
 void* binlog_suffix ; 
 char* binlogname ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int cutoff_seconds ; 
 int /*<<< orphan*/  do_merge () ; 
 scalar_t__ dyn_cur ; 
 scalar_t__ dyn_first ; 
 scalar_t__ dyn_last ; 
 int /*<<< orphan*/  dyn_purge_all_deleted_messages () ; 
 TYPE_1__* dyn_user_header (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__* fd ; 
 int /*<<< orphan*/  flush_out () ; 
 char** fnames ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int* fsize ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 scalar_t__ load_next_user () ; 
 scalar_t__ log_cutoff_pos ; 
 scalar_t__ log_pos ; 
 scalar_t__ log_wpos ; 
 scalar_t__ lseek (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 void* metaindex_suffix ; 
 int /*<<< orphan*/  my_sort (int /*<<< orphan*/ ,int) ; 
 char* new_logname ; 
 char* new_metaindexname ; 
 int now ; 
 int /*<<< orphan*/ * obuff ; 
 char* old_logname ; 
 int /*<<< orphan*/  open_file (int,char*,int) ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  output_stats () ; 
 char* progname ; 
 int purged_msgs_cnt ; 
 int read (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replay_log (int) ; 
 scalar_t__ rpos ; 
 int /*<<< orphan*/  set_log_data (scalar_t__,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,void*) ; 
 int start_time ; 
 int /*<<< orphan*/  stderr ; 
 int time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 int /*<<< orphan*/  users_added ; 
 int /*<<< orphan*/  users_dropped ; 
 int verbosity ; 
 scalar_t__ wpos ; 
 int write (scalar_t__,int /*<<< orphan*/ *,int) ; 

int main (int argc, char *argv[]) {
  int i;

  progname = argv[0];
  while ((i = getopt (argc, argv, "hvu:c:a:i:")) != -1) {
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
    case 'a':
      binlog_suffix = optarg;
      break;
    case 'i':
      metaindex_suffix = optarg;
      break;
    case 'c':
      cutoff_seconds = atoi(optarg);
      if (cutoff_seconds > 1000000 || cutoff_seconds < 0) {
	cutoff_seconds = DEFAULT_CUTOFF_SECONDS;
      }
    }
  }
  if (argc != optind + 2) {
    usage();
    return 2;
  }

  if (username && change_user(username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit(1);
  }

  open_file (0, argv[optind], 0);
  snprintf (old_logname, 254, "%s%s", argv[optind], binlog_suffix);
  binlogname = old_logname;
  open_file (1, old_logname, 0);

  open_file (2, argv[optind+1], 1);
  if (fsize[2]) {
    fprintf (stderr, "new huge index file %s already exists and is not empty\n", fnames[2]);
    return 1;
  }

  snprintf (new_logname, 254, "%s%s", argv[optind+1], binlog_suffix);
  open_file (3, new_logname, 1);
  if (fsize[3]) {
    fprintf (stderr, "new binlog file %s already exists and is not empty\n", fnames[3]);
    return 1;
  }

  snprintf (new_metaindexname, 254, "%s%s", argv[optind+1], metaindex_suffix);
  open_file (4, new_metaindexname, 1);
  if (fsize[4]) {
    fprintf (stderr, "new metaindex file %s already exists and is not empty\n", fnames[4]);
    return 1;
  }

  init_dyn_data();

  start_time = now = time(0);

  if (fsize[1] && fd[1]) {
    if (verbosity) {
      fprintf (stderr, "replaying binlog file %s (size %lld), cutoff time=%d\n", binlogname, fsize[1], start_time - cutoff_seconds);
    }
    binlog_load_time = get_utime(CLOCK_MONOTONIC);

    clear_log ();
    set_log_data (fd[1], fsize[1]);
    replay_log (start_time - cutoff_seconds);

    binlog_load_time = get_utime(CLOCK_MONOTONIC) - binlog_load_time;
    binlog_loaded_size = log_pos;

    if (log_cutoff_pos < 0) {
      log_cutoff_pos = log_pos;
    }

    if (verbosity) {
      fprintf (stderr, "replay binlog file: done, pos=%lld, cutoff_pos=%lld, alloc_mem=%ld out of %ld, time %.06lfs\n", 
	       (long long) log_pos, (long long) log_cutoff_pos, (long) (dyn_cur - dyn_first), (long) (dyn_last - dyn_first), binlog_load_time);
    }
  }

  clear_log();
  dyn_purge_all_deleted_messages();

  if (verbosity) {
    fprintf (stderr, "purged %d recently added and deleted messages\n", purged_msgs_cnt);
    fprintf (stderr, "scanning data file \"%s\", size=%lld\n", fnames[0], fsize[0]);
  }

  while (load_next_user() > 0) {
    if (User.user_id && (unsigned) User.user_id < MAX_USER_ID) {
      UserMod = dyn_user_header (User.user_id, 0);
      if (UserMod && UserMod->delmsg_cnt == -239) {
	fprintf (stderr, "duplicate user id %d in file %s at position %lld\n", User.user_id, fnames[0], (long long) rpos);
      } else {
	// fprintf (stderr, "processing user %ld\n", User.user_id);
	do_merge ();
	if (UserMod) {
	  UserMod->delmsg_cnt = -239;
	}
      }
    } else {
      users_dropped++;
      fprintf (stderr, "dropping messages of user %d (user_id out of bounds)\n", User.user_id);
    }
  }

  if (verbosity) {
    fprintf (stderr, "scanning new users...\n");
  }

  User.magic = MAIL_INDEX_BLOCK_MAGIC;

  for (i = 0; i < PRIME; i++) {
    UserMod = UserModHeaders[i];
    if (UserMod && UserMod->delmsg_cnt != -239) {
      User.user_id = Users[i];
      users_added++;
      if (User.user_id && (unsigned) User.user_id < MAX_USER_ID) {
	User.hash_cnt = User.list_cnt = 0;
	CurH = 0;
	CurL = 0;
	if (verbosity > 1) {
	  fprintf (stderr, "adding new user %d\n", User.user_id);
	}
	do_merge ();
      } else {
	users_dropped++;
	fprintf (stderr, "ignoring messages of new user %d (user_id out of bounds)\n", User.user_id);
      }
    }
  }
 
  flush_out();

  if (verbosity) {
    fprintf (stderr, "file %s created, total size %lld\n", fnames[2], (long long) wpos);
  }
  close (fd[2]);

  my_sort (0, M_cnt - 1);

  for (i = 0; i < M_cnt; i++) {
    MetaB[i] = *MetaP[i];
  }
  i = write (fd[4], MetaB, M_cnt * sizeof(userlist_entry_t));
  assert (i == M_cnt * sizeof(userlist_entry_t));
  close (fd[4]);

  if (verbosity) {
    fprintf (stderr, "%d userlist entries (%ld bytes) written to %s\n", M_cnt, (long)M_cnt*sizeof(userlist_entry_t), fnames[4]);
  }

  assert (lseek (fd[1], log_cutoff_pos, SEEK_SET) >= 0);
  do {
    i = read(fd[1], obuff, FILE_BUFFER_SIZE);
    assert (write (fd[3], obuff, i) == i);
    log_wpos += i;
  } while (i);
  close (fd[3]);

  if (verbosity) {
    fprintf (stderr, "%lld bytes copied from old binlog %s, position %lld to new binlog %s\n", (long long) log_wpos, fnames[1], (long long) log_cutoff_pos, fnames[3]);
    output_stats();
  }

  return 0;
}