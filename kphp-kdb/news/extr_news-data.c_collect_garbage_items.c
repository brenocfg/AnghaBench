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
struct TYPE_8__ {int tot_items; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_9__ {int total_items; } ;
typedef  TYPE_2__ recommend_user_t ;
struct TYPE_10__ {int total_items; } ;
typedef  TYPE_3__ notify_user_t ;

/* Variables and functions */
 int MAX_USERS ; 
 scalar_t__ NOTIFY_MODE ; 
 int RECOMMEND_MODE ; 
 scalar_t__ UG_MODE ; 
 TYPE_1__** User ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delete_user_by_idx (int) ; 
 int /*<<< orphan*/  garbage_objects_collected ; 
 int garbage_uid ; 
 int /*<<< orphan*/  garbage_users_collected ; 
 int items_kept ; 
 int /*<<< orphan*/  remove_old_items (TYPE_1__*) ; 
 int /*<<< orphan*/  remove_old_notify_items (TYPE_3__*) ; 
 int /*<<< orphan*/  remove_old_recommend_items (TYPE_2__*) ; 

__attribute__((used)) static inline int collect_garbage_items (int steps) {
  assert (UG_MODE || NOTIFY_MODE || RECOMMEND_MODE);
  int old_items_kept = items_kept;
  int i = garbage_uid, seek_steps = steps * 10;
  do {
    assert (i >= 0 && i < MAX_USERS);
    user_t *M = User[i];
    if (M) {
      int t;
      if (UG_MODE) {
        remove_old_items (M);
        t = M->tot_items;
      } else if (NOTIFY_MODE) {
        remove_old_notify_items ((notify_user_t *) M);
        t = ((notify_user_t *) M)->total_items;
      } else {
        assert (RECOMMEND_MODE);
        remove_old_recommend_items ((recommend_user_t *) M);
        t = ((recommend_user_t *) M)->total_items;
      }
      if (!t && RECOMMEND_MODE) {
        garbage_users_collected++;
        delete_user_by_idx (i);
      }
      steps--;
    }
    i += 239;
    if (i >= MAX_USERS) {
      i -= MAX_USERS;
    }
  } while (i != garbage_uid && steps > 0 && --seek_steps > 0);
  garbage_uid = i;
  garbage_objects_collected += old_items_kept - items_kept;
  return 1;
}