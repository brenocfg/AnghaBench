#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  field_desc ;
struct TYPE_6__ {size_t v_fid; int type; int v_int; long long v_long; double v_double; int /*<<< orphan*/  v_raw_len; int /*<<< orphan*/  v_raw; int /*<<< orphan*/  v_string_len; int /*<<< orphan*/  v_string; } ;
typedef  TYPE_1__ field ;
struct TYPE_7__ {int type_id; char** tval; size_t tn; int* tp; size_t* id; int size; } ;
typedef  TYPE_2__ event_dump ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_8__ {int /*<<< orphan*/ * fields; } ;

/* Variables and functions */
 char* GET_FIELD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ has_field (int /*<<< orphan*/ *,size_t) ; 
 char* raw_tmp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  t_double 132 
#define  t_int 131 
#define  t_long 130 
#define  t_raw 129 
#define  t_string 128 
 char* tmp_mem_strdupn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* types ; 

int event_dump_from_field (event_dump *d, field *f, int type_id, event *e) {
  assert (d->type_id == type_id);

  field_desc *ff = types[type_id].fields;
  char *dest;
  int flag = 0;
  if (e != NULL && has_field (e, f->v_fid) && f->type != t_string && f->type != t_raw) {
    dest = GET_FIELD (e, &ff[f->v_fid]);
  } else {
    dest = d->tval[d->tn];
    flag = 1;
  }

  int add = 0;
  switch (f->type) {
  case t_int:
    *(int *)dest = f->v_int;
    add = 4;
    break;
  case t_long:
    *(long long *)dest = f->v_long;
    add = 8;
    break;
  case t_double:
    *(double *)dest = f->v_double;
    add = 8;
    break;
  case t_string:
    *(char **)dest = tmp_mem_strdupn (f->v_string, f->v_string_len);
    add = f->v_string_len + 1;
    break;
  case t_raw:
    add = f->v_raw_len + sizeof (short);
    *(char **)dest = raw_tmp_create (f->v_raw, f->v_raw_len);
    break;
  default:
    assert (0);
  }

  if (flag) {
    d->tp[d->tn] = f->type;
    d->id[d->tn] = f->v_fid;
    d->size += add;
    d->tn++;
  }

  //d->size += types[type_id].shifts_len;

  return 0;
}