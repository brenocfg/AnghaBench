#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  local_id; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  predicate ;

/* Variables and functions */
 size_t ALBUM_TYPE ; 
 int MAX_RESULT ; 
 int /*<<< orphan*/  NOAIO ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* conv_uid_get (int) ; 
 int /*<<< orphan*/  dbg (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 char* debug_buff ; 
 scalar_t__ debug_error ; 
 int /*<<< orphan*/  debug_init () ; 
 int event_get_album_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_to_array (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 
 int get_fields (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * predicate_init (char*,size_t) ; 
 int /*<<< orphan*/ * result_obj ; 
 int /*<<< orphan*/  return_fields ; 
 int /*<<< orphan*/ * types ; 
 int user_get_albums (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int user_get_albums_count (TYPE_1__*) ; 
 int user_get_albums_count_pred (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int user_get_photos_count (TYPE_1__*,int) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int /*<<< orphan*/  write_only ; 

int get_albums (int uid, int offset, int limit, char *fields, const int reverse, const int count, char *condition, char **result) {
  dbg ("get_albums (uid = %d) (fields = %s) (offset = %d) (limit = %d)\n", uid, fields, offset, limit);
  assert (!index_mode && !write_only);

  *result = debug_buff;
  debug_init();

  user *u = conv_uid_get (uid);
  int fields_n = get_fields (&types[ALBUM_TYPE], fields);

  if (u == NULL || fields_n < 0) {
    return 0;
  }

  if (offset < 0) {
    offset = 0;
  }

  if (offset > MAX_RESULT) {
    offset = MAX_RESULT;
  }

  if (limit <= 0) {
    limit = 0;
  }

  if (limit > MAX_RESULT) {
    limit = MAX_RESULT;
  }

  load_user_metafile (u, u->local_id, NOAIO);
  if (!user_loaded (u)) {
    return -2;
  }

  predicate *pred = predicate_init (condition, ALBUM_TYPE);

  int i, ii, total, real_total;
  if (reverse) {
    total = user_get_albums_count_pred (u, pred);
    real_total = total;
    assert (total >= 0);

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
      total = user_get_albums_count_pred (u, pred);
      real_total = total;
      assert (total >= 0);

      total -= offset;

      if (total < 0) {
        total = 0;
      }
    } else {
      total = user_get_albums (u, offset, limit, pred);
      real_total = user_get_albums_count (u);
      assert (total >= 0);
    }
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

    int aid = event_get_album_id (&result_obj[i]);

    if (fields_n == 0) {
      debug ("i:%d;i:%d;", aid, count ? user_get_photos_count (u, aid) : aid);
    } else {
      debug ("i:%d;%s", aid, event_to_array (&result_obj[i], ALBUM_TYPE, return_fields, fields_n));
    }
  }
  debug ("}");

  if (debug_error) {
    return 0;
  }

  return 1;
}