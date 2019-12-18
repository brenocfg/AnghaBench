#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int type; } ;
typedef  TYPE_1__ field_desc ;
struct TYPE_22__ {int type_id; int tn; char** tval; int* id; int* tp; int size; } ;
typedef  TYPE_2__ event_dump ;
struct TYPE_23__ {int sn; } ;
typedef  TYPE_3__ event ;
struct TYPE_24__ {TYPE_1__* fields; } ;

/* Variables and functions */
 double* GET_DOUBLE (TYPE_3__*,TYPE_1__*) ; 
 char* GET_FIELD (TYPE_3__*,TYPE_1__*) ; 
 int* GET_INT (TYPE_3__*,TYPE_1__*) ; 
 long long* GET_LONG (TYPE_3__*,TYPE_1__*) ; 
 char* GET_RAW (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GET_STRING (TYPE_3__*,TYPE_1__*) ; 
 int RAW_RLEN (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ has_field (TYPE_3__*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
#define  t_double 132 
#define  t_int 131 
#define  t_long 130 
#define  t_raw 129 
#define  t_string 128 
 char* tmp_mem_dup (char*,int) ; 
 char* tmp_mem_strdup (int /*<<< orphan*/ ) ; 
 TYPE_4__* types ; 

int event_dump_from_event (event_dump *d, event *e, int type_id, event *v) {
  int i, j;

  if (e == NULL) {
    return 0;
  }

  assert (d->type_id == type_id);

//  d->tn = 0;
//  d->size = 0;
//  d->type_id = type_id;

  field_desc *f = types[type_id].fields;

  int tn = d->tn;

  for (i = 0; i < e->sn; i++) {
    if (has_field (e, i)) {
      char *dest;
      int flag = 0, add = 0;
      if (v != NULL && has_field (v, i) && f[i].type != t_string && f[i].type != t_raw) {
        dest = GET_FIELD (v, &f[i]);
      } else {
        dest = d->tval[d->tn];
        flag = 1;
      }

      j = tn;
      switch (f[i].type) {
      case t_int:
        *(int *)dest = *GET_INT (e, &f[i]);
        add = sizeof (int);
        break;
      case t_long:
        *(long long *)dest = *GET_LONG (e, &f[i]);
        add = sizeof (long long);
        break;
      case t_double:
        *(double *)dest = *GET_DOUBLE (e, &f[i]);
        add = sizeof (double);
        break;
      case t_string:
        //TODO: it can be optimized
        for (j = 0; j < tn; j++) {
          if (d->id[j] == i) {
            break;
          }
        }

        if (j == tn) {
          *(char **)d->tval[d->tn] = tmp_mem_strdup (GET_STRING (e, &f[i]));
          add = strlen (*(char **)d->tval[d->tn]) + 1;
        }
        break;
      case t_raw:
        for (j = 0; j < tn; j++) {
          if (d->id[j] == i) {
            break;
          }
        }

        if (j == tn) {
          char *x = GET_RAW (e, &f[i]);
          add = RAW_RLEN (x);
          *(char **)d->tval[d->tn] = tmp_mem_dup (x, add);
        }
        break;
      }
      if (flag && j == tn) {
        d->id[d->tn] = i;
        d->tp[d->tn] = f[i].type;
        d->size += add;
        d->tn++;
      }
    }
  }
  return 0;
}