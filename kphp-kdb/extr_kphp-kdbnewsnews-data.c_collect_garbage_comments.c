#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* hnext; } ;
typedef  TYPE_1__ place_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_MODE ; 
 int PLACES_HASH ; 
 TYPE_1__** Place ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int const comments_kept ; 
 int /*<<< orphan*/  garbage_objects_collected ; 
 int garbage_uid ; 
 int /*<<< orphan*/  remove_old_comments (TYPE_1__*) ; 

__attribute__((used)) static inline int collect_garbage_comments (int steps) {
  assert (COMM_MODE);
  const int old_comments_kept = comments_kept;
  int i = garbage_uid, max_uid = PLACES_HASH, seek_steps = steps * 10;
  do {
    place_t *M = Place[i];
    while (M) {
      remove_old_comments (M);
      steps--;
      M = M->hnext;
    }
    i++;
    if (i >= max_uid) {
      i -= max_uid;
    }
  } while (i != garbage_uid && steps > 0 && --seek_steps > 0);
  garbage_uid = i;
  garbage_objects_collected += old_comments_kept - comments_kept;
  return 1;
}