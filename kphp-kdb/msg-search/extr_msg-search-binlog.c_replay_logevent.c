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
struct log_event {int type; int user_id; int /*<<< orphan*/  msg_id; } ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
#define  LE_DELMSG_MAGIC 132 
#define  LE_DELOLDMSG_MAGIC 131 
 unsigned int LE_NEWMSG_MAGIC ; 
 unsigned int LE_NEWMSG_MAGIC_MAX ; 
#define  LE_PAD_MAGIC 130 
#define  LE_TIMESTAMP_MAGIC 129 
#define  LE_UNDELMSG_MAGIC 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dyn_alloc_new_msg (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dyn_delall_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_delete_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_undelete_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_user_header (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ log_cutoff_pos ; 
 int log_first_ts ; 
 int /*<<< orphan*/  log_pos ; 
 int log_read_until ; 
 int log_scan_mode ; 
 int log_time_cutoff ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verbosity ; 

int replay_logevent (struct log_event *E, int size) {
  int l = E->type - LE_NEWMSG_MAGIC;
  hash_t *p;

  if (size < 4) { return -2; }

  if ((unsigned) l < LE_NEWMSG_MAGIC_MAX - LE_NEWMSG_MAGIC) {
    if (size < l * 8 + 12) { return -1; }
    if (!log_scan_mode) {
      p = dyn_alloc_new_msg (E->user_id, E->msg_id, l);
      assert (p);
      memcpy (p, ((char *) E) + 12, l * 8);
    }
    return l * 8 + 12;
  }

  switch (E->type) {
  case LE_PAD_MAGIC:
    return 4;
  case LE_DELMSG_MAGIC:
    if (size < 12) { return -2; }
    if (!log_scan_mode) {
      dyn_delete_msg (dyn_user_header (E->user_id, 1), E->msg_id);
    }
    return 12;
  case LE_UNDELMSG_MAGIC:
    if (size < 12) { return -2; }
    dyn_undelete_msg (dyn_user_header (E->user_id, 1), E->msg_id);
    return 12;
  case LE_DELOLDMSG_MAGIC:
    if (size < 12) { return -2; }
    dyn_delall_msg (dyn_user_header (E->user_id, 1), E->msg_id);
    return 12;
  case LE_TIMESTAMP_MAGIC:
    if (size < 8) { return -2; }
    if (!log_first_ts) {
      log_first_ts = E->user_id;
    }
    if (log_read_until > E->user_id) {
      fprintf (stderr, "time goes back from %d to %d in log file\n", log_read_until, E->user_id);
    }
    log_read_until = E->user_id;
    if (E->user_id >= log_time_cutoff && !log_scan_mode) {
      log_cutoff_pos = log_pos - size;
      log_scan_mode = 1;
      if (verbosity) {
	fprintf (stderr, "reached timestamp %d above cutoff %d at binlog position %lld, entering scan mode 1\n",
		 E->user_id, log_time_cutoff, (long long) log_cutoff_pos);
      }
    }
    return 8;
  }
  fprintf (stderr, "unknown magic in log file: %08x\n", E->type);
  return -1;
}