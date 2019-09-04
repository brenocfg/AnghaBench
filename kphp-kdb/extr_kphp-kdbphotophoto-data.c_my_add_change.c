#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  my_dyn_object ;
struct TYPE_2__ {scalar_t__ tp; int /*<<< orphan*/  fn; int /*<<< orphan*/  f; int /*<<< orphan*/ * e; } ;
typedef  TYPE_1__ my_change ;
typedef  int /*<<< orphan*/  event ;
typedef  int /*<<< orphan*/  dyn_object ;
typedef  int /*<<< orphan*/  change ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ch_event ; 
 scalar_t__ ch_fields ; 
 int /*<<< orphan*/  event_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * event_update_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * event_update_php (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

inline int my_add_change (dyn_object **_o, change *_c, int type_id) {
  my_dyn_object **o =  (my_dyn_object **)_o;
  my_change *c = (my_change *)_c;

  event *ne;
  if (c->tp == ch_event) {
    if (*o == NULL) {
      ne = c->e;
    } else {
      ne = event_update_event (*o, c->e, type_id);
      event_free (c->e);
    }
  } else if (c->tp == ch_fields) {
    ne = event_update_php (*o, c->f, c->fn, type_id);
  } else {
    assert ("wtf" && 0);
  }

  if (*o != ne) {
    event_free (*o);
    *o = ne;
  }
  return 0;
}