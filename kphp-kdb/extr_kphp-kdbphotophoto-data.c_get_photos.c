#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  local_id; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  predicate ;

/* Variables and functions */
 int MAX_RESULT ; 
 int /*<<< orphan*/  NOAIO ; 
 size_t PHOTO_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* conv_uid_get (int) ; 
 int /*<<< orphan*/  dbg (char*,int,int,int,int,int const) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 char* debug_buff ; 
 scalar_t__ debug_error ; 
 int /*<<< orphan*/  debug_init () ; 
 int event_get_photo_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_to_array (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 
 int get_fields (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * predicate_init (char*,size_t) ; 
 int /*<<< orphan*/ * result_obj ; 
 int /*<<< orphan*/  return_fields ; 
 int /*<<< orphan*/ * types ; 
 int user_get_photos (TYPE_1__*,int,int,int,int /*<<< orphan*/ *) ; 
 int user_get_photos_count (TYPE_1__*,int) ; 
 int user_get_photos_count_pred (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int /*<<< orphan*/  write_only ; 

int get_photos (int uid, int aid, int offset, int limit, char *fields, const int reverse, const int count, char *condition, char **result) {
  dbg ("get photos: (uid = %d) (aid = %d) (offset = %d) (limit = %d) (reverse = %d)\n", uid, aid, offset, limit, reverse);
  assert (!index_mode && !write_only);

  *result = debug_buff;
  debug_init();

  user *u = conv_uid_get (uid);
  int fields_n = get_fields (&types[PHOTO_TYPE], fields);

  if (u == NULL || fields_n < 0) {
    return 0;
  }

  if (offset < 0) {
    offset = 0;
  }

  if (offset > MAX_RESULT) {
    offset = MAX_RESULT;
  }

  if (limit < 0) {
    limit = 0;
  }

  if (limit > MAX_RESULT) {
    limit = MAX_RESULT;
  }

  load_user_metafile (u, u->local_id, NOAIO);
  if (!user_loaded (u)) {
    return -2;
  }

  predicate *pred = predicate_init (condition, PHOTO_TYPE);

  int i, ii, total, real_total;
  if (reverse) {
    total = user_get_photos_count_pred (u, aid, pred);
    real_total = total;

    if (total < 0) {
      return 0;
    }

    offset = total - offset - limit;
    if (offset < 0) {
      limit += offset;
      offset = 0;
    }
    if (limit < 0) {
      limit = 0;
    }
  } else {
    if (count && pred != NULL) {
      total = user_get_photos_count_pred (u, aid, pred);
      real_total = total;

      if (total < 0) {
        return 0;
      }

      total -= offset;

      if (total < 0) {
        total = 0;
      }
    } else {
      total = user_get_photos (u, aid, offset, limit, pred);
      real_total = user_get_photos_count (u, aid);
    }
  }

  if (total < 0) {
    return 0;
  }
  if (total > limit) {
    total = limit;
  }

  debug ("a:%d:{", total + count);
  if (count) {
    debug ("s:5:\"count\";i:%d;", real_total);
  }
  for (ii = 0; ii < total; ii++) {
    if (reverse) {
      i = total - ii - 1 + offset;
    } else {
      if (count && pred != NULL) {
        i = ii + offset;
      } else {
        i = ii;
      }
    }

    int pid = event_get_photo_id (&result_obj[i]);

    if (fields_n == 0) {
      debug ("i:%d;i:%d;", pid, pid);
    } else {
      debug ("i:%d;%s", pid, event_to_array (&result_obj[i], PHOTO_TYPE, return_fields, fields_n));
    }
  }
  debug ("}");

  if (debug_error) {
    return 0;
  }

  return 1;
}