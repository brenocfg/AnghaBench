#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  local_id; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  predicate ;

/* Variables and functions */
 int /*<<< orphan*/  NOAIO ; 
 int /*<<< orphan*/  PHOTO_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* conv_uid_get (int) ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * predicate_init (char*,int /*<<< orphan*/ ) ; 
 int user_get_photos_count (TYPE_1__*,int) ; 
 int user_get_photos_count_pred (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int /*<<< orphan*/  write_only ; 

int get_photos_count (int uid, int aid, char *condition) {
  assert (!index_mode && !write_only);

  user *u = conv_uid_get (uid);
  if (u == NULL) {
    return -1;
  }

  load_user_metafile (u, u->local_id, NOAIO);
  if (!user_loaded (u)) {
    return -2;
  }

  predicate *pred = predicate_init (condition, PHOTO_TYPE);

  if (pred == NULL) {
    return user_get_photos_count (u, aid);
  } else {
    return user_get_photos_count_pred (u, aid, pred);
  }
}