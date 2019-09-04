#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tn; } ;
typedef  TYPE_1__ event_dump ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * create_event (TYPE_1__*) ; 
 int event_dump_from_event (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_dump_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tmp_mem_init () ; 

event *event_update_event (event *e, event *v, int type_id) {
  if (v == NULL) {
    return e;
  }

  tmp_mem_init();

  event_dump d;
  event_dump_init (&d, type_id);

  assert (event_dump_from_event (&d, v, type_id, e) > -1);

  if (d.tn) {
    event_dump_from_event (&d, e, type_id, NULL);

    e = create_event (&d);
    assert (e != NULL);
  }
  return e;
}