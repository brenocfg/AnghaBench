#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_13__ {int currId; } ;
struct TYPE_14__ {int object_old_n; char* object_data; int* object_indexes; char** object_names; int /*<<< orphan*/  pref_table; int /*<<< orphan*/  object_chg; TYPE_12__ object_table; int /*<<< orphan*/  changed_objs; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ user ;
typedef  float rating ;
typedef  TYPE_2__* change_list_ptr ;
struct TYPE_15__ {int type; int x; char* s; int val; int cnt; scalar_t__ timestamp; int /*<<< orphan*/  number; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ change_list ;

/* Variables and functions */
 scalar_t__ GET_USER_RATING_STATE (int /*<<< orphan*/ ) ; 
 int MAX_CNT ; 
 float MAX_RATING ; 
 int MAX_RATING_NUM ; 
 int MEM_FLAG ; 
 float RATING_NORM ; 
 int /*<<< orphan*/  SET_USER_RATING_STATE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TYPE_ID (int,int) ; 
 scalar_t__ add_on_increment ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  chg_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  chg_del (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dl_free (char*,int) ; 
 char* dl_malloc (int) ; 
 int expf (float) ; 
 scalar_t__ fading ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  friend_changes ; 
 long long* gen_hashes (char*) ; 
 int /*<<< orphan*/  htbl_add (int /*<<< orphan*/ *,long long,int) ; 
 int /*<<< orphan*/  htbl_del (int /*<<< orphan*/ *,long long,int) ; 
 int ltbl_add (TYPE_12__*,int /*<<< orphan*/ ) ; 
 int* max_cnt_type ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ ratingT ; 
 int /*<<< orphan*/  rating_incr (float*,int,scalar_t__) ; 
 int rating_num ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int user_get_object_local_id (TYPE_1__*,int,int) ; 
 char* user_get_object_name (TYPE_1__*,int) ; 
 float* user_get_object_rating (TYPE_1__*,int,int) ; 
 scalar_t__ user_has_local_object (TYPE_1__*,int) ; 
 int user_has_object (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  user_upd_object_size (TYPE_1__*) ; 
 int /*<<< orphan*/  vct_add (int /*<<< orphan*/ *,int) ; 
 int verbosity ; 

void user_do_change (user *u, change_list_ptr change) {
/*  {
    int id = ltbl_get_rev (&user_table, (int)(u - users)), x = change->x, type = change->type, tm = change->timestamp, num = change->number;
    char *s = change->s;
    fprintf (stderr, "do change user = %d %d:%d, timestamp = %d, number = %d <", id, type, x, tm, num);
    fprintf (stderr, "%ld><", (long)s);

    if (s == NULL || change->x <= 0 || type >= 256) {
      fprintf (stderr, "NULL>\n");
    } else {
      fprintf (stderr, "%s>\n", s);
    }
  }*/

  int type = change->type;
  int local_id;

  if (change->x == 0) {
    if (type == 0) {
      //Rating nullify
      int object_n, num;
      for (object_n = u->object_old_n + u->object_table.currId - 1; object_n > 0; object_n--) {
        for (num = 0; num < rating_num; num++) {
          *user_get_object_rating (u, object_n, num) = 0.0f;
        }
      }
    } else if (type == 1 || type == 2) {
      //Set rating state
      u->flags = SET_USER_RATING_STATE(u->flags, type - 1);
    } else {
      assert (0);
    }
    return;
  }

  if (change->x < 0) {
    if (GET_USER_RATING_STATE(u->flags) == 0) {
      return;
    }

    int num = type / 256;
    int x = -change->x;
    type %= 256;
    local_id = user_has_object (u, type, x);

#ifdef NOHINTS
    if (!local_id && add_on_increment) {
      change_list tmp;
      tmp.next = NULL;
      tmp.s = NULL;
      tmp.x = x;
      tmp.type = type;
      tmp.timestamp = change->timestamp;
      tmp.number = change->number;

      user_do_change (u, &tmp);
      local_id = user_has_object (u, type, x);
    }
#endif

    if (verbosity > 1) {
      fprintf (stderr, "Incrementing object of type %d, object_id = %d, local_id = %d\n", type, x, local_id);
    }

    if (local_id != 0) {
      if (num >= MAX_RATING_NUM) { //set obj rating
        if (fading) {
          *user_get_object_rating (u, local_id, num - MAX_RATING_NUM) = (rating)(change->val * expf (((rating)(change->timestamp - ratingT)) / RATING_NORM));
        } else {
          rating *a = user_get_object_rating (u, local_id, num - MAX_RATING_NUM);
          *a = change->val;
          if (*a < -MAX_RATING) {
            *a = -MAX_RATING;
          }
          if (*a > MAX_RATING) {
            *a = MAX_RATING;
          }
        }
      } else {
        rating_incr (user_get_object_rating (u, local_id, num), change->cnt, change->timestamp);
      }
    }
    return;
  }

  if (type >= 256) { // global change type
    type -= 256;
    int new_type = change->cnt;

    assert (0 < type && type < 256);
    assert (0 < new_type && new_type < 256);

    local_id = user_get_object_local_id (u, type, change->x);

    if (verbosity > 1) {
      fprintf (stderr, "Changing type of object with type %d, object_id = %d, local_id = %d to type %d\n", type, change->x, local_id, new_type);
    }

    if (user_has_local_object (u, local_id)) {
      change_list tmp;
      tmp.next = NULL;
#ifdef HINTS
      tmp.s = user_get_object_name (u, local_id);
#else
      tmp.s = NULL;
#endif
      tmp.x = change->x;
      tmp.type = new_type;
      tmp.timestamp = change->timestamp;
      tmp.number = change->number;

      user_do_change (u, &tmp);


      int new_local_id = user_get_object_local_id (u, new_type, change->x);
      if (new_local_id == 0) {
        return;
      }

      int num;
      for (num = 0; num < rating_num; num++) {
        *user_get_object_rating (u, new_local_id, num) = *user_get_object_rating (u, local_id, num);
      }

#ifdef HINTS
      tmp.s = NULL;
#endif
      tmp.type = -type;

      user_do_change (u, &tmp);
    }

    return;
  }

  int is_del;
  if (type < 0) {
    is_del = 1;
    type = -type;
  } else {
    is_del = 0;
  }

#ifdef HINTS
  char *s, **s_ptr = NULL;
  int s_in_mtf = 0;
#endif

  if (is_del == 1) {
    assert (change->s == NULL);
    local_id = user_has_object (u, type, change->x);

    if (verbosity > 1) {
      fprintf (stderr, "Deleting object of type %d, object_id = %d, local_id = %d\n", type, change->x, local_id);
    }

    if (local_id == 0) {
      return; // object doesn't exist (do not need to delete)
    }

#ifdef HINTS
    if (local_id <= u->object_old_n) {
      s_ptr = ((char **)(u->object_data + (u->object_indexes[local_id] & ~MEM_FLAG)));
      if (u->object_indexes[local_id] & MEM_FLAG) {
        s = *s_ptr;
      } else {
        s_in_mtf = 1;
        s = (u->object_data + u->object_indexes[local_id]);
        u->object_indexes[local_id] |= MEM_FLAG;
        vct_add (&u->changed_objs, local_id);
      }
    } else {
      s_ptr = &u->object_names[local_id - u->object_old_n];
      s = *s_ptr;
    }
#else
    chg_del (&u->object_chg, local_id * 2 + 1);
#endif
  } else {
#ifdef HINTS
    assert (change->s != NULL);
#else
    assert (change->s == NULL);
#endif

    local_id = user_get_object_local_id (u, type, change->x);
    if (verbosity > 1) {
      fprintf (stderr, "Adding object of type %d, object_id = %d, local_id = %d\n", type, change->x, local_id);
    }

    if (user_has_local_object (u, local_id)) {
#ifdef HINTS
      change_list tmp;
      tmp.next = NULL;
      tmp.s = NULL;
      tmp.x = change->x;
      tmp.type = -type;
      tmp.timestamp = change->timestamp;
      tmp.number = change->number;

      user_do_change (u, &tmp);
#else
      return;
#endif
    } else {
      if (local_id == 0) {
        if (u->object_old_n + u->object_table.currId + 1 < MAX_CNT - (max_cnt_type[type] < MAX_CNT) * MAX_CNT / 10) {
          local_id = ltbl_add (&u->object_table, TYPE_ID(type, change->x)) + u->object_old_n;

          user_upd_object_size (u);

          if (fading) {
            int num;

            for (num = 0; num < rating_num; num++) {
              rating_incr (user_get_object_rating (u, local_id, num), 1, change->timestamp);
            }
          }

          if (type == 10) {
            friend_changes++;
          }
        } else {
          return;
        }

        if (verbosity > 1) {
          fprintf (stderr, "Adding object of type %d, object_id = %d, local_id = %d\n", type, change->x, local_id);
        }
      }
    }
#ifdef NOHINTS
    chg_add (&u->object_chg, local_id * 2 + 1);
#endif

    user_upd_object_size (u);

#ifdef HINTS
    assert (user_get_object_name (u, local_id) == NULL);

    int len = (strlen (change->s) + 1) * sizeof (char);
    s = dl_malloc (len);
    memcpy (s, change->s, len);

    if (local_id <= u->object_old_n) {
      *((char **)(u->object_data + (u->object_indexes[local_id] & ~MEM_FLAG))) = s;

      assert (u->object_indexes[local_id] & MEM_FLAG);
    } else {
      u->object_names[local_id - u->object_old_n] = s;
    }
#endif
  }

#ifdef HINTS
  assert (s != NULL);

//  fprintf (stderr, "   %s for object id = %d <%s>\n", is_del ? "del" : "add", local_id, s);

  long long *v = gen_hashes (s);
  int i;
  for (i = 0; v[i]; i++) {
    if (is_del) {
      htbl_del (&u->pref_table, v[i], local_id);
    } else {
      htbl_add (&u->pref_table, v[i], local_id);
    }
  }

  if (is_del) {
    if (!s_in_mtf) {
      dl_free (s, (strlen (s) + 1) * sizeof (char));
    }
    *s_ptr = NULL;
  }
#endif
}