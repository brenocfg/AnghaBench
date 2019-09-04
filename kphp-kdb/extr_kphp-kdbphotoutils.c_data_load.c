#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  n; } ;
struct TYPE_4__ {int objects_n; int* objects_offset; char* objects; TYPE_2__ hidden_state; int /*<<< orphan*/  prm; int /*<<< orphan*/  restore_info; int /*<<< orphan*/  id_to_local_id; } ;
typedef  TYPE_1__ data ;

/* Variables and functions */
 int /*<<< orphan*/  PERM (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_INT (char*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  inc_pass ; 
 int /*<<< orphan*/  lookup_load (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  lookup_load_old (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  read_restore (int*,int,int /*<<< orphan*/ *) ; 

void data_load (data *d, char *metafile, int metafile_len) {
  char *s = metafile, *t = s + metafile_len;

  int init_perm = d->objects_n == -2;

  READ_INT (s, d->objects_n);

//  dbg ("LOAD DATA: (objects_n = %d) (metafile_len = %d)\n", d->objects_n, metafile_len);
  //dbg ("crc32 = %d\n", compute_crc32 (metafile, metafile_len));
  //DUMP (metafile, metafile_len);

  d->objects_offset = (int *)s;
  s += sizeof (int) * (d->objects_n + 1);

  //TODO: check it
  s += lookup_load_old (&d->id_to_local_id, s, t - s, d->objects_n);

  d->objects = s;

  s = d->objects + d->objects_offset[d->objects_n];

  if (t != s && d->objects_n) {// new index
    int lookup_len;
    assert (s + sizeof (int) <= t);
    READ_INT (s, lookup_len);
    assert (s + lookup_len <= t);
    lookup_load (&d->hidden_state, s, lookup_len);
    s += lookup_len;

    if (init_perm) {
      int restore_n;
      assert (s + sizeof (int) <= t);
      READ_INT (s, restore_n);

      int restore_len = sizeof (int) * restore_n;
      assert (s + restore_len <= t);
      s += read_restore ((int *)s, restore_n, &d->restore_info);
    }
    //assert (s == s + restore_len);
  } else {
    lookup_load (&d->hidden_state, NULL, 0);
  }
  //s += lookup_load (d->id_to_local_id, s, t - s);

  //d->ids = (int *)s;
  //s += sizeof (int) * d->objects_n;

  //d->old_perm = (int *)s;
  //s += sizeof (int) * d->objects_n;

  //assert (s <= t);

  if (init_perm) {
    //PERM (inc, &d->prm, d->objects_n);
    PERM (inc_pass, &d->prm, d->objects_n, d->hidden_state.n);
  }


  //if (DATA_FUNC (d)->object_onload != NULL) {
  //  int i;
  //  actual_object o;
  //  for (i = 0; i < d->objects_n; i++) {
  //    data_get_actual_object (d, i, &o);
  //    int f = o->dyn != NULL;
  //    DATA_FUNC (d)->object_onload (&o);
  //    if (f && o->dyn == NULL) {
  //      map_int_vptr_del (&d->dyn_snapshots, local_id + 1);
  //    }
  //  }
  //}
}