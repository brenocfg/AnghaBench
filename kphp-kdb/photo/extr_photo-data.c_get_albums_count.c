#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  local_id; } ;
typedef  TYPE_1__ user ;
typedef  int /*<<< orphan*/  predicate ;

/* Variables and functions */
 int /*<<< orphan*/  ALBUM_TYPE ; 
 int /*<<< orphan*/  MAX_ALBUMS ; 
 int /*<<< orphan*/  NOAIO ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* conv_uid_get (int) ; 
 int event_get_album_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * predicate_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * result_obj ; 
 int user_get_albums (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int /*<<< orphan*/  write_only ; 

int get_albums_count (int uid, char *condition) {
  assert (!index_mode && !write_only);

  user *u = conv_uid_get (uid);
  if (u == NULL) {
    return -1;
  }

  load_user_metafile (u, u->local_id, NOAIO);
  if (!user_loaded (u)) {
    return -2;
  }

  predicate *pred = predicate_init (condition, ALBUM_TYPE);

  int res = user_get_albums (u, 0, MAX_ALBUMS, pred);

  int i, real_res = 0;
  for (i = 0; i < res; i++) {
    int aid = event_get_album_id (&result_obj[i]);

    if (aid > 0) {
      real_res++;
    }
  }

  return real_res;
}