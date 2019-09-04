#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* treap_node_ptr ;
struct TYPE_9__ {int /*<<< orphan*/  subscr_cnt; int /*<<< orphan*/  keys_cnt; int /*<<< orphan*/  ev_first; int /*<<< orphan*/  ref_cnt; int /*<<< orphan*/  name; int /*<<< orphan*/ * subs; } ;
typedef  TYPE_2__ queue ;
struct TYPE_10__ {int y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ pli ;
typedef  int /*<<< orphan*/  ll ;
struct TYPE_8__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_event (TYPE_2__*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical (char*,int,int,...) ; 
 TYPE_2__* get_news_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_to_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  insert_to_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_changes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  to_add ; 
 scalar_t__ to_add_n ; 
 int /*<<< orphan*/  to_del ; 
 scalar_t__ to_del_n ; 
 TYPE_1__* treap_fnd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void add_event_to_news (ll from_id, int x, int y, int ttl, pli *ids, int idn, char *event, int need_debug) {
  int len = strlen (event), i;

  to_add_n = 0;
  to_del_n = 0;

  for (i = 0; i < idn; i++) {
    if (!IS_UID(ids[i].x)) {
      queue *q = get_news_queue (ids[i].x, 0);

      if (q != NULL) {
        assert (q->subs != NULL);
        treap_node_ptr v = treap_fnd (q->subs, from_id);

        if (need_debug) {
          critical ("BAD REDIRECT from %lld to %lld[%s](we are here) : ref_cnt = %d, ev_first = %p, keys_cnt = %d, subscr_cnt = %d, ttl = %d\n", from_id, ids[i].x, q->name, q->ref_cnt, q->ev_first, q->keys_cnt, q->subscr_cnt, ttl);
          if (v != NULL) {
            critical ("  ids[i].y = %d, v->val = %d, x = %d, y = %d, %d =?= %d\n", ids[i].y, v->val, x, y,
                x & v->val, y);
          }
        }
        if (v != NULL) {
          if (v->val != ids[i].y) {
            insert_to_add (ids[i].x, v->val);
            //dbg ("ADD %lld->%lld\n", ids[i].x, from_id);
          }

          if ((x & v->val) == y) {
            int yn = sprintf (event + len, "<!>%d", v->val);
            add_event (q, event, len + yn, x, y, ttl);
          }
        } else {
          insert_to_del (ids[i].x);
        }
      } else {
        if (need_debug) {
          critical ("BAD REDIRECT from %lld to NULL, ttl = %d\n", from_id, ttl);
        }
        insert_to_del (ids[i].x);
      }
    }
  }
  process_changes (from_id, NULL, to_add, to_add_n, 1, 1);
  process_changes (from_id, NULL, to_del, to_del_n, 0, 1);
}