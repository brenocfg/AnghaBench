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
struct lev_start {int dummy; } ;
struct lev_generic {int type; int b; } ;

/* Variables and functions */
#define  LEV_CRC32 137 
#define  LEV_MF_ADD_EXCEPTION 136 
#define  LEV_MF_CLEAR_EXCEPTIONS 135 
#define  LEV_MF_DEL_EXCEPTION 134 
#define  LEV_NOOP 133 
#define  LEV_ROTATE_FROM 132 
#define  LEV_ROTATE_TO 131 
#define  LEV_START 130 
#define  LEV_TAG 129 
#define  LEV_TIMESTAMP 128 
 int MEMORY_CHANGES_PERCENT ; 
 int /*<<< orphan*/  STANDARD_LOG_EVENT_HANDLER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _eventsLeft ; 
 int /*<<< orphan*/  add_exception ; 
 int /*<<< orphan*/  clear_exceptions ; 
 int default_replay_logevent (struct lev_generic*,int) ; 
 int /*<<< orphan*/  del_exception ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int get_memory_used () ; 
 scalar_t__ index_mode ; 
 int /*<<< orphan*/  lev_mf ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 int max_memory ; 
 int /*<<< orphan*/  mf_le_start (struct lev_start*) ; 
 int /*<<< orphan*/  newindexname ; 
 int /*<<< orphan*/  save_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int mf_replay_logevent (struct lev_generic *E, int size) {
//  fprintf (stderr, "mf_replay_logevent %lld\n", log_cur_pos());
//  fprintf (stderr, "%x\n", E->type);
  if (index_mode) {
    if ((_eventsLeft && --_eventsLeft == 0) || get_memory_used() > MEMORY_CHANGES_PERCENT * max_memory) {
      save_index (newindexname);
      exit (13);
    }
  }

  int s;
  switch (E->type) {
  case LEV_START:
    if (size < 24 || E->b < 0 || E->b > 4096) { return -2; }
    s = 24 + ((E->b + 3) & -4);
    if (size < s) { return -2; }
    return mf_le_start ((struct lev_start *) E) >= 0 ? s : -1;
  case LEV_NOOP:
  case LEV_TIMESTAMP:
  case LEV_CRC32:
  case LEV_ROTATE_FROM:
  case LEV_ROTATE_TO:
  case LEV_TAG:
    return default_replay_logevent (E, size);
  case LEV_MF_ADD_EXCEPTION:
    STANDARD_LOG_EVENT_HANDLER(lev_mf, add_exception);
  case LEV_MF_DEL_EXCEPTION:
    STANDARD_LOG_EVENT_HANDLER(lev_mf, del_exception);
  case LEV_MF_CLEAR_EXCEPTIONS:
    STANDARD_LOG_EVENT_HANDLER(lev_mf, clear_exceptions);
  }

  fprintf (stderr, "unknown log event type %08x at position %lld\n", E->type, log_cur_pos());

  return -1;
}