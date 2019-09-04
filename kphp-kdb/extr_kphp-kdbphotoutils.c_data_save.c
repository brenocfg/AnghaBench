#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int objects_n; int new_objects_n; int /*<<< orphan*/  restore_info; int /*<<< orphan*/  hidden_state; int /*<<< orphan*/  prm; int /*<<< orphan*/  id_to_local_id; } ;
typedef  TYPE_1__ data ;
typedef  int /*<<< orphan*/  actual_object ;
struct TYPE_9__ {int (* object_save ) (int /*<<< orphan*/ *,char*,int) ;} ;

/* Variables and functions */
 int CONV_ID (int) ; 
 TYPE_6__* DATA_FUNC (TYPE_1__*) ; 
 int PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_INT (char*,int) ; 
 int* _restore_info ; 
 int _restore_info_maxn ; 
 int _restore_info_n ; 
 int /*<<< orphan*/  assert (int) ; 
 int data_get_actual_object (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int data_get_hidden_state (TYPE_1__*,int) ; 
 int /*<<< orphan*/  data_restore_append (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  dl_free (int*,size_t) ; 
 int* dl_malloc (int) ; 
 int* dl_malloc0 (size_t) ; 
 int /*<<< orphan*/  dump_restore ; 
 int lookup_save (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int lookup_save_expected_len (int /*<<< orphan*/ *) ; 
 int lookup_save_prepare (int /*<<< orphan*/ *,int*,int*,int,int) ; 
 int /*<<< orphan*/  lookup_set (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  map_int_vptr_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int,size_t) ; 
 int /*<<< orphan*/  slice ; 
 int stub1 (int /*<<< orphan*/ *,char*,int) ; 

int data_save (data *d, char *buf, int buf_size, int max_objects_n, int *deleted, int *deleted_n_ptr, int deleted_max_n) {
  int i;

  char *s = buf;
  int sn = buf_size;

  int max_local_id = d->objects_n + d->new_objects_n + 1;

  if (max_objects_n < 0 || max_objects_n > max_local_id) {
    max_objects_n = max_local_id;
  }


  int c_mx_n = lookup_save_expected_len (&d->id_to_local_id);

  size_t c_size = sizeof (int) * c_mx_n;
  int *cx = dl_malloc (c_size),
      *cy = dl_malloc (c_size);

  int cn = lookup_save_prepare (&d->id_to_local_id, cx, cy, c_mx_n, -1), ci = 0;

  size_t hidden_ids_size = sizeof (int) * lookup_save_expected_len (&d->hidden_state);
  int *hidden_ids = dl_malloc (hidden_ids_size),
    hidden_ids_n = 0;

  // gen permutation of unhidden elements
  assert (max_local_id >= cn);
  size_t perm_size = sizeof (int) * max_local_id;
  int *perm = dl_malloc (perm_size),
      *perm_flag = dl_malloc0 (perm_size),
      *inv_perm = dl_malloc (perm_size),
      *next = dl_malloc (perm_size);

  int n = PERM (slice, &d->prm, perm, cn, 0);
  assert (n <= cn);

  int shift;
  if (max_objects_n < n) {
    shift = n - max_objects_n;
  } else {
    shift = 0;
  }

  // gen inversed permutation
  for (i = 0; i < n; i++) {
    inv_perm[perm[i]] = i;
  }

  //init next
  for (i = 0; i < n; i++) {
    next[perm[i]] = perm[i];
  }

  //dbg ("hidden photos expected count = %d\n", data_hide_expected_size (d));

  int deleted_n = 0;
  for (i = 0; i < cn; i++) {
    int id = cx[i],
      local_id = cy[i];

    int hidden_state = data_get_hidden_state (d, id);

    if (hidden_state != 0) {
      hidden_state--;
      lookup_set (&d->hidden_state, cx[i], hidden_state) ;

      if (hidden_state != 0) {
        assert (hidden_state > 0);
        cx[ci] = id;
        cy[ci] = local_id;
        ci++;

        hidden_ids[hidden_ids_n++] = local_id;
      } else {
        if (deleted != NULL && deleted_n < deleted_max_n) {
          deleted[deleted_n] = id;
        }
        deleted_n++;
      }
    } else {
      if (shift <= 0) {
        cx[ci] = id;
        cy[ci] = local_id;

        ci++;
      } else {
        int pos = inv_perm[local_id];
        if (pos == 0) {
          next[local_id] = -1;
        } else {
          next[local_id] = perm[pos - 1];
        }
        perm_flag[pos] = 1;

        if (deleted != NULL && deleted_n < deleted_max_n) {
          deleted[deleted_n] = id;
        }
        deleted_n++;
        shift--;
      }
    }
  }

  size_t new_local_id_size = sizeof (int) * max_local_id;
  int *new_local_id = dl_malloc (new_local_id_size);
  memset (new_local_id, -1, new_local_id_size);

  size_t new_perm_size = sizeof (int) * ci;
  int *new_perm = dl_malloc (new_perm_size);
  int new_perm_n = 0;

  int cur_id = 0;
  for (i = 0; i < hidden_ids_n; i++) {
    //dbg ("nhidden (old_id = %d) -> (new_id = %d)\n", hidden_ids[i], cur_id);
    int id = hidden_ids[i];

    new_perm[cur_id] = id;
    new_local_id[id] = cur_id++;
  }

  for (i = 0; i < n; i++) {
    int id = perm[i];
    if (perm_flag[i]) { // deleted
      next[id] = next[id] == -1 ? -1 : next[next[id]];
      if (next[id] != -1) {
        assert (next[next[id]] == next[id]);
      }
      data_restore_append (d, next[id], id);
    } else {
      assert (next[id] == id);

      //dbg ("uhidden (old_id = %d) -> (new_id = %d)\n", id, cur_id);
      new_perm[cur_id] = id;
      new_local_id[id] = cur_id++;
    }
  }
  new_perm_n = cur_id;

  assert (new_perm_n == ci);

  for (i = 0; i < ci; i++) {
    int y = cy[i];
    cy[i] = new_local_id[y];
    assert (cy[i] != -1);
    //new_local_id[y] = -1;
  }

  if (deleted_n_ptr != NULL) {
    *deleted_n_ptr = deleted_n;
  }

  //dbg ("(hidden_n = %d) (deleted_n = %d) (cur_id - hidden_n = %d) == (cn = %d)\n", hidden_ids_n, deleted_n, cur_id - hidden_ids_n, cn);

  assert ((int)sizeof (int) <= sn);
  assert (ci >= 0);
  WRITE_INT (s, ci);
  sn -= sizeof (int);

  int header_size = sizeof (int) * (ci + 1);
  int *header = (int *)s;

  assert (header_size <= sn);
  s += header_size;
  sn -= header_size;

  //TODO: no n in old metafile, just 2 arrays
  int ids_size = sizeof (int) * ci;
  assert (ids_size <= sn);
  memcpy (s, cx, ids_size);
  s += ids_size;
  sn -= ids_size;


  int old_perm_size = sizeof (int) * ci;
  assert (old_perm_size <= sn);
  memcpy (s, cy, old_perm_size);
  s += old_perm_size;
  sn -= old_perm_size;


  actual_object o;
  char *st = s;
  for (i = 0; i < ci; i++) {
    header[i] = s - st;
    assert (data_get_actual_object (d, new_perm[i], &o) > -1);
    int len = DATA_FUNC(d)->object_save (&o, s, sn);
    s += len;
    sn -= len;
    assert (sn >= 0);
  }
  header[ci] = s - st;

  assert ((int)sizeof (int) <= sn);
  int *lookup_len = (int *)s;
  s += sizeof (int);
  sn -= sizeof (int);
  s += *lookup_len = lookup_save (&d->hidden_state, s, sn, 0);
  sn -= *lookup_len;


  //DUMP (st, s - st);

  _restore_info_maxn = max_local_id;
  int _restore_info_size = sizeof (int) * _restore_info_maxn;
  _restore_info = dl_malloc (_restore_info_size);
  _restore_info_n = 0;

  map_int_vptr_foreach (&d->restore_info, dump_restore);

  int *restore = _restore_info, restore_n = 0, f = 0;
  for (i = 0; i < _restore_info_n; i++) {
    int x = restore[i];
    if (x < 0) {
      //dbg ("{%d}\n", CONV_ID (x));
      if (f) {
        restore_n--;
      }

      x = CONV_ID (x);
      x = x == -1 ? -1 : next[x];

      if (x != -1) {
        assert (new_local_id[x] >= hidden_ids_n);
        assert (next[x] == x);
      }
      x = x == -1 ? -1 : new_local_id[x];
      restore[restore_n++] = CONV_ID (x);
      f = 1;
    } else {
      //dbg ("---%d\n", x);
      x = new_local_id [x];

      if (x >= 0) {
        assert (x < hidden_ids_n);
        restore[restore_n++] = x;
        f = 0;
      }
    }
  }
  if (f == 1) {
    restore_n--;
  }

  assert ((int)sizeof (int) <= sn);
  WRITE_INT (s, restore_n);
  sn -= sizeof (int);

  size_t restore_size = sizeof (int) * restore_n;
  assert ((int)restore_size < sn);
  memcpy (s, restore, restore_size);
  s += restore_size;
  sn -= restore_size;


  dl_free (hidden_ids, hidden_ids_size);

  dl_free (perm, perm_size);
  dl_free (perm_flag, perm_size);
  dl_free (inv_perm, perm_size);
  dl_free (next, perm_size);

  dl_free (cx, c_size);
  dl_free (cy, c_size);

  dl_free (new_local_id, new_local_id_size);

  dl_free (_restore_info, _restore_info_size);
  dl_free (new_perm, new_perm_size);

  //dbg ("data_save: crc32 = %d\n", compute_crc32 (buf, s - buf));
  //DUMP (buf, s - buf);
  return s - buf;
}