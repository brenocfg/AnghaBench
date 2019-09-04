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
struct TYPE_4__ {int /*<<< orphan*/  new_exceptions; } ;
typedef  TYPE_1__ user ;
struct lev_magus_add_exception_string {int type; int /*<<< orphan*/  text; int /*<<< orphan*/  user_id; } ;
struct TYPE_5__ {int fid_names_cnt; int objs_limit; int /*<<< orphan*/ * fid_names_begins; int /*<<< orphan*/  fid_id_str; scalar_t__ has_names; } ;

/* Variables and functions */
 int LEV_MAGUS_ADD_EXCEPTION_STRING ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* conv_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hset_int_add (int /*<<< orphan*/ *,int) ; 
 int index_mode ; 
 int* map_string_int_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* map_string_int_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* sim_header ; 
 scalar_t__* types ; 

int add_exception_string (struct lev_magus_add_exception_string *E) {
  user *u = conv_uid (E->user_id);

  if (u == NULL) {
    return 0;
  }

  int type = E->type - LEV_MAGUS_ADD_EXCEPTION_STRING;
  assert (0 < type && type < 256);

  assert (types[type] && sim_header[type].has_names);

  int *fid = map_string_int_get (&sim_header[type].fid_id_str, E->text);
  if (fid == NULL && index_mode) {
    int *cnt = &sim_header[type].fid_names_cnt;
    assert (*cnt < sim_header[type].objs_limit * 2 + 1024000 * index_mode + 1);
    sim_header[type].fid_names_begins[*cnt] = dl_strdup (E->text);
    fid = map_string_int_add (&sim_header[type].fid_id_str, sim_header[type].fid_names_begins[*cnt]);
    *fid = *cnt;
    *cnt = (*cnt) + 1;
  }
  if (fid == NULL) {
    return 0;
  }

  assert (0 <= *fid && *fid < (1 << 23));

  hset_int_add (&u->new_exceptions, (type << 23) + *fid);

  return 1;
}