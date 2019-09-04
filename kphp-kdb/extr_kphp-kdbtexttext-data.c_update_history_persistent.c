#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ first_pq; struct incore_persistent_history* persistent_history; } ;
typedef  TYPE_1__ user_t ;
struct incore_persistent_history {int alloc_events; int cur_events; int* history; } ;

/* Variables and functions */
 int MIN_PERSISTENT_HISTORY_EVENTS ; 
 scalar_t__ USER_PCONN (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int incore_persistent_history_bytes ; 
 int /*<<< orphan*/  incore_persistent_history_events ; 
 int /*<<< orphan*/  incore_persistent_history_lists ; 
 struct incore_persistent_history* malloc (int) ; 
 int /*<<< orphan*/  persistent_history_enabled ; 
 int /*<<< orphan*/  process_user_persistent_query_queue2 (TYPE_1__*) ; 
 struct incore_persistent_history* realloc (struct incore_persistent_history*,int) ; 

__attribute__((used)) static void update_history_persistent (user_t *U, int local_id, int flags, int op) {
  assert (U && local_id > 0 && (unsigned) op <= 5);
  if (!persistent_history_enabled) {
    return;
  }
  struct incore_persistent_history *H = U->persistent_history;
  if (!H) {
    H = U->persistent_history = malloc (sizeof (struct incore_persistent_history) + 8 * MIN_PERSISTENT_HISTORY_EVENTS);
    H->alloc_events = MIN_PERSISTENT_HISTORY_EVENTS;
    H->cur_events = 0;
    incore_persistent_history_bytes += sizeof (struct incore_persistent_history) + H->alloc_events * 8;
    incore_persistent_history_lists++;
  } else if (H->cur_events == H->alloc_events) {
    H = U->persistent_history = realloc (H, sizeof (struct incore_persistent_history) + 16 * H->alloc_events);
    incore_persistent_history_bytes += H->alloc_events * 8;
    H->alloc_events *= 2;
  }
  int *p = H->history + H->cur_events++ * 2;
  p[0] = local_id;
  p[1] = (flags & 0xffff) | (op << 24);
  incore_persistent_history_events++;

  if (U->first_pq != USER_PCONN (U)) {
    process_user_persistent_query_queue2 (U);
  }
}