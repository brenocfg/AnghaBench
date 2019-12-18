#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user ;
typedef  int /*<<< orphan*/  entry_t ;
typedef  int /*<<< orphan*/  black_list ;
struct TYPE_14__ {int /*<<< orphan*/  cnt; } ;
struct TYPE_13__ {int size; } ;
struct TYPE_11__ {int /*<<< orphan*/  cnt; } ;
struct TYPE_12__ {int /*<<< orphan*/ * next; TYPE_1__ b; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* bl_head ; 
 int /*<<< orphan*/  black_list_do_delete (TYPE_2__*) ; 
 TYPE_2__* buff ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free_header (int /*<<< orphan*/ *) ; 
 scalar_t__ get_memory_used () ; 
 TYPE_7__ global_bayes ; 
 int /*<<< orphan*/  header ; 
 scalar_t__ htbl_get_memory () ; 
 scalar_t__ index_mode ; 
 int /*<<< orphan*/  ltbl_free (TYPE_3__*) ; 
 int max_words ; 
 TYPE_2__* new_buff ; 
 int /*<<< orphan*/  qfree (TYPE_2__*,int) ; 
 int /*<<< orphan*/  qhtbl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int user_LRU_unload () ; 
 TYPE_3__ user_table ; 
 TYPE_2__* users ; 
 scalar_t__ verbosity ; 

void free_all (void) {
  if (verbosity) {
    while (user_LRU_unload() != -1) {
    }

    qhtbl_free (&global_bayes.cnt);
    int i;
    for (i = 0; i < user_table.size; i++) {
      qhtbl_free (&users[i].b.cnt);
    }

    if (index_mode) {
      qfree (buff, max_words * sizeof (entry_t));
      qfree (new_buff, 4000000 * sizeof (entry_t));
    }

    while (bl_head->next != NULL) {
      black_list_do_delete (bl_head);
    }
    qfree (bl_head, sizeof (black_list));

    qfree (users, sizeof (user) * user_table.size);

    ltbl_free (&user_table);
    free_header (&header);

    fprintf (stderr, "Memory left: %ld\n", get_memory_used() - htbl_get_memory());
    assert (get_memory_used() - htbl_get_memory() == 0);
  }
}