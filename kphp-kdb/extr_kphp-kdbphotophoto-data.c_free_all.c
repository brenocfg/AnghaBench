#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  user ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_types () ; 
 int /*<<< orphan*/  h_users ; 
 int /*<<< orphan*/  header ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  map_int_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_intp_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int user_LRU_unload () ; 
 int user_cnt ; 
 int /*<<< orphan*/  user_unloaded_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * users ; 
 int /*<<< orphan*/  utils_free () ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  volumes ; 
 int /*<<< orphan*/  write_only ; 

void free_all (void) {
  if (verbosity > 0) {
    while (user_LRU_unload() != -1) {
    }

    if (!write_only && !index_mode) {
      int i;
      for (i = 1; i < user_cnt; i++) {
        user *u = &users[i];
        user_unloaded_free (u);
      }
    }
    dl_free (users, sizeof (user) * user_cnt);

    map_int_int_free (&volumes);
    set_intp_free (&h_users);
    free_header (&header);

    free_types();

    utils_free();

    fprintf (stderr, "Memory left: %lld\n", dl_get_memory_used());
    assert (dl_get_memory_used() == 0);
  }
}