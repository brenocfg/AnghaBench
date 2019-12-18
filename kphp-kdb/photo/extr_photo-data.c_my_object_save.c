#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* name; int type; } ;
typedef  TYPE_1__ field_desc ;
typedef  int /*<<< orphan*/  event ;
struct TYPE_11__ {int /*<<< orphan*/  dyn; int /*<<< orphan*/ * obj; } ;
typedef  TYPE_2__ actual_object ;
struct TYPE_12__ {TYPE_1__* fields; } ;

/* Variables and functions */
 scalar_t__ EMPTY__METAFILE ; 
 int /*<<< orphan*/ * GET_DOUBLE (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int* GET_INT (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * GET_LONG (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GET_RAW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* GET_STRING (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int PHOTO_TYPE ; 
 int RAW_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  event_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * event_update_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int get_event_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_field (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
#define  t_double 132 
#define  t_int 131 
#define  t_long 130 
#define  t_raw 129 
#define  t_string 128 
 int /*<<< orphan*/  total_photos ; 
 TYPE_3__* types ; 

inline int my_object_save (actual_object *o, char *buf, int buf_size, int type_id) {
  if (type_id == PHOTO_TYPE) {
    total_photos++;
  }

  event *old = o->obj == (event *)EMPTY__METAFILE ? NULL : o->obj, *new = old;
  event *e = event_update_event (new, o->dyn, type_id);

  if (0) {
    int k;
    for (k = 0; k < 63; k++) {
      if (!has_field (e, k)) {
        continue;
      }

      field_desc *f = &types[type_id].fields[k];
      fprintf (stderr, "%15s: ", f->name);

      switch (f->type) {
        case t_int:
          fprintf (stderr, "%d", *GET_INT(e, f));
          break;
        case t_long:
          fprintf (stderr, "%lld", *GET_LONG(e, f));
          break;
        case t_double:
          fprintf (stderr, "%.6lf", *GET_DOUBLE(e, f));
          break;
        case t_string: {
          char *p = GET_STRING(e, f);
          while (*p) {
            switch (*p) {
              case '\t':
              case '\n':
              case '\\':
                fputc ('\\', stderr);
              default:
                fputc (*p++, stderr);
            }
          }
          break;
        }
        case t_raw:
          fprintf (stderr, "%d", RAW_LEN (GET_RAW (e, f)));
          break;
        default:
          assert (0);
      }
      fprintf (stderr, "\n");
    }
    fprintf (stderr, "\n");
  }

  int len = get_event_size (e);
  assert (len <= buf_size);
  memcpy (buf, e, len);

  if (e != new) {
    event_free (e);
  }
  if (new != old) {
    event_free (new);
  }
  return len;
}