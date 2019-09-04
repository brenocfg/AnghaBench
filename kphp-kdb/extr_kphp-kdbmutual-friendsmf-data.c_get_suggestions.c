#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  root; } ;
struct TYPE_12__ {TYPE_1__ sugg; } ;
typedef  TYPE_2__ user ;
struct TYPE_13__ {int y; int x; int /*<<< orphan*/  r; int /*<<< orphan*/  l; } ;
typedef  TYPE_3__ trp_node ;

/* Variables and functions */
 int MAX_CNT ; 
 int /*<<< orphan*/  NOAIO ; 
 int /*<<< orphan*/  add_user_used (TYPE_2__*) ; 
 TYPE_2__* conv_uid (int) ; 
 int /*<<< orphan*/  del_user_used (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_add (int /*<<< orphan*/ ) ; 
 TYPE_3__* heap_get () ; 
 int /*<<< orphan*/  heap_init () ; 
 scalar_t__ heap_size ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int local_uid (int) ; 
 int /*<<< orphan*/  user_has_exception (TYPE_2__*,int) ; 
 int /*<<< orphan*/  user_loaded (TYPE_2__*) ; 

int get_suggestions (int uid, int mx_cnt, int min_common, int *res) {
  user *u = conv_uid (uid);
  int local_id = local_uid (uid);

  if (mx_cnt > MAX_CNT) {
    mx_cnt = MAX_CNT;
  }

  if (u == NULL) {
    res[0] = 0;
    return 0;
  }

  min_common *= 4;
  if (min_common < 4) {
    min_common = 4;
  }

  load_user_metafile (u, local_id, NOAIO);

//  fprintf (stderr, "after load_user_metafile. u->metafile_len = %d\n", u->metafile_len);

  if (!user_loaded (u)) {
    return -2;
  }

  del_user_used (u);
  add_user_used (u);

  heap_init ();
  int n = 0;

  heap_add (u->sugg.root);
  while (heap_size && mx_cnt) {
    trp_node *v = heap_get();

    if ((v->y >> 16) < min_common) {
      //TODO: comment for testing
      break;
    }

    if (!user_has_exception (u, v->x)) {
      res[n * 2 + 1] = v->x;
      res[n * 2 + 2] = v->y >> 16;
      n++;

      mx_cnt--;
    }
    heap_add (v->l);
    heap_add (v->r);
  }

  res[0] = n;

  return 1;
}