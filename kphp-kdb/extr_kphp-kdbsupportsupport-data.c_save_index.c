#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  log_pos1_crc32; int /*<<< orphan*/  log_split_mod; int /*<<< orphan*/  log_split_max; int /*<<< orphan*/  log_split_min; int /*<<< orphan*/  log_timestamp; scalar_t__ log_pos1; int /*<<< orphan*/  created_at; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ index_header ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_8__ {int /*<<< orphan*/  replica_prefix; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SUPPORT_INDEX_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_disabled ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 TYPE_4__* engine_snapshot_replica ; 
 int /*<<< orphan*/  exit (int) ; 
 int* fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fsync (int) ; 
 long long get_index_header_size (TYPE_1__*) ; 
 char* get_new_snapshot_name (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ jump_log_pos ; 
 int /*<<< orphan*/  log_crc32_complement ; 
 scalar_t__ log_cur_pos () ; 
 int /*<<< orphan*/  log_last_ts ; 
 int /*<<< orphan*/  log_split_max ; 
 int /*<<< orphan*/  log_split_min ; 
 int /*<<< orphan*/  log_split_mod ; 
 long long lseek (int,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  print_snapshot_name (char*) ; 
 int /*<<< orphan*/  relax_log_crc32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relax_write_log_crc32 () ; 
 scalar_t__ rename_temporary_snapshot (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ verbosity ; 
 int write (int,TYPE_1__*,int) ; 

int save_index (void) {
  char *newidxname = NULL;

  dbg ("save_index\n");
  if (engine_snapshot_replica) {
    newidxname = get_new_snapshot_name (engine_snapshot_replica, log_cur_pos(), engine_snapshot_replica->replica_prefix);
  }

  if (!newidxname || newidxname[0] == '-') {
    fprintf (stderr, "cannot write index: cannot compute its name\n");
    exit (1);
  }

  if (log_cur_pos() == jump_log_pos) {
    fprintf (stderr, "skipping generation of new snapshot %s for position %lld: snapshot for this position already exists\n",
       newidxname, jump_log_pos);
    return 0;
  }

  if (verbosity > 0) {
    fprintf (stderr, "creating index %s at log position %lld\n", newidxname, log_cur_pos());
  }

  if (!binlog_disabled) {
    relax_write_log_crc32();
  } else {
    relax_log_crc32 (0);
  }

  index_header header;
  memset (&header, 0, sizeof (header));

  fd[1] = open (newidxname, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL, 0660);
  if (fd[1] < 0) {
    fprintf (stderr, "cannot create new index file %s: %m\n", newidxname);
    exit (1);
  }

  header.magic = SUPPORT_INDEX_MAGIC;
  header.created_at = time (NULL);

  long long fCurr = get_index_header_size (&header);
  assert (lseek (fd[1], fCurr, SEEK_SET) == fCurr);

  // write header
  header.log_pos1 = log_cur_pos();
  header.log_timestamp = log_last_ts;
  header.log_split_min = log_split_min;
  header.log_split_max = log_split_max;
  header.log_split_mod = log_split_mod;
  relax_log_crc32 (0);
  header.log_pos1_crc32 = ~log_crc32_complement;

  assert (lseek (fd[1], 0, SEEK_SET) == 0);
  assert (write (fd[1], &header, sizeof (header)) == sizeof (header));

  assert (fsync (fd[1]) >= 0);
  assert (close (fd[1]) >= 0);
  fd[1] = -1;

  if (rename_temporary_snapshot (newidxname)) {
    fprintf (stderr, "cannot rename new index file from %s: %m\n", newidxname);
    unlink (newidxname);
    exit (1);
  }

  print_snapshot_name (newidxname);
  return 0;
}