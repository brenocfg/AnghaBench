#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* answers_list_ptr ;
typedef  int /*<<< orphan*/  answers_list ;
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; struct TYPE_6__* E; } ;

/* Variables and functions */
 TYPE_1__* answers ; 
 scalar_t__ answers_cnt ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dl_free (TYPE_1__*,int) ; 
 scalar_t__ dl_get_memory_used () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int get_lev_support_add_answer_size (TYPE_1__*) ; 
 int /*<<< orphan*/  key_words ; 
 int /*<<< orphan*/  map_int_int_free (int /*<<< orphan*/ *) ; 
 scalar_t__ map_int_int_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_int_set_int_free (int /*<<< orphan*/ *) ; 
 scalar_t__ map_int_set_int_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_int_vptr_free (int /*<<< orphan*/ *) ; 
 scalar_t__ map_int_vptr_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_answer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  q_cnt ; 
 int /*<<< orphan*/  set_int_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  user_id_to_answer ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  word_to_answers ; 

void free_all (void) {
  if (verbosity) {
    while (answers_cnt > 0) {
      assert (answers->next != answers);
      process_answer (answers->next, -1);

      answers_list_ptr next = answers->next;
      dl_free (next->E, get_lev_support_add_answer_size (next->E));
      answers->next = next->next;
      answers->next->prev = answers;

      dl_free (next, sizeof (answers_list));
    }
    assert (answers->next == answers);

    assert (map_int_int_used (&q_cnt) == 0);
    assert (map_int_vptr_used (&user_id_to_answer) == 0);
    assert (map_int_set_int_used (&word_to_answers) == 0);

    set_int_free (&key_words);
    map_int_int_free (&q_cnt);
    map_int_vptr_free (&user_id_to_answer);
    map_int_set_int_free (&word_to_answers);

    dl_free (answers, sizeof (answers_list));

    fprintf (stderr, "Memory left: %ld\n", (long)dl_get_memory_used());
    assert (dl_get_memory_used() == 0);
  }
}