#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int memory_buf_mx; } ;

/* Variables and functions */
 int MAX_LETTER_SIZE ; 
 int MAX_PRIORITY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_close_file (int) ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ ,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/ * drive_l_to_letter ; 
 int /*<<< orphan*/  flush_all (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_2__ header ; 
 int /*<<< orphan*/  id_to_letter ; 
 int /*<<< orphan*/  letter_buf ; 
 int /*<<< orphan*/  letter_buf_get ; 
 int /*<<< orphan*/  letter_delete_time (int,char*) ; 
 int /*<<< orphan*/  map_ll_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_ll_vptr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * memory_buf ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  task_deletes ; 
 int /*<<< orphan*/  task_id_to_delete_time ; 
 int /*<<< orphan*/  vector_free (int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

void free_all (void) {
  //TODO truncate files
  letter_delete_time (-1, "Engine restart");

  flush_all (1);

  int i;
  dl_close_file (1);
  for (i = 0; i < MAX_PRIORITY; i++) {
    dl_close_file (2 + i);
  }

  if (verbosity > 0) {
    map_ll_vptr_free (&id_to_letter);
    for (i = 0; i < MAX_PRIORITY; i++) {
      map_ll_vptr_free (&drive_l_to_letter[i]);
    }

    vector_free (task_deletes);
    map_ll_int_free (&task_id_to_delete_time);

    for (i = 0; i < MAX_PRIORITY; i++) {
      dl_free (memory_buf[i], header.data[i].memory_buf_mx);
    }

    dl_free (letter_buf, 2 * MAX_LETTER_SIZE + 1100);
    dl_free (letter_buf_get, 2 * MAX_LETTER_SIZE + 1100);
    fprintf (stderr, "Memory left: %lld\n", dl_get_memory_used());
//    while (1) {}
    assert (dl_get_memory_used() == 0);
  }
}