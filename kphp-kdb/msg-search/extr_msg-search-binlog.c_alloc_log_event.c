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
struct log_event {int type; int user_id; int msg_id; } ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int LE_TIMESTAMP_MAGIC ; 
 int MAX_LOG_TS_INTERVAL ; 
 int /*<<< orphan*/  binlogname ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int log_end ; 
 int log_endw ; 
 int log_last_ts ; 
 int log_rptr ; 
 int log_start ; 
 int log_wptr ; 
 int now ; 
 int /*<<< orphan*/  stderr ; 
 int time (int /*<<< orphan*/ ) ; 

hash_t *alloc_log_event (int type, int user_id, int message_id, int extra) {
  int b = 12 + 8 * extra;
  struct log_event *EV;
  if (!binlogname) {
    return 0;
  }
  if (type == LE_TIMESTAMP_MAGIC) {
    b = 8;
    user_id = now ? now : time(0);
    if (log_last_ts < user_id) {
      log_last_ts = user_id;
    }
  } else if (now > log_last_ts + MAX_LOG_TS_INTERVAL) {
    alloc_log_event (LE_TIMESTAMP_MAGIC, 0, 0, 0);
  }
  if (b > log_end - log_wptr) {
    log_endw = log_wptr;
    log_wptr = log_start;
  }
  if (log_wptr < log_rptr && log_wptr + b >= log_rptr) {
    fprintf (stderr, "fatal: binlog buffer overflow!\n");
    exit(3);
  }
  EV = (struct log_event *) log_wptr;
  log_wptr += b;

  EV->type = type;
  EV->user_id = user_id;

  if (type == LE_TIMESTAMP_MAGIC) {
    return 0;
  }

  EV->msg_id = message_id;
  return (hash_t *) (((char *) EV) + 12);
}