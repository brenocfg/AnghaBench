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

/* Variables and functions */
 int FLAG_ENTRY_SORT_SEARCH ; 
 int FLAG_PRIORITY_SORT_SEARCH ; 
 int FLAG_REVERSE_SEARCH ; 
 int MAX_RATES ; 
 int Q_order ; 
 int Q_type ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * evaluate_rating ; 
 int /*<<< orphan*/ * evaluate_relevance_search_rating ; 
 int /*<<< orphan*/ * get_rating ; 
 int /*<<< orphan*/ * get_rating_as_object_id ; 
 int /*<<< orphan*/ * mix_priority_with_object_id ; 
 int /*<<< orphan*/ * mix_priority_with_rating ; 
 int /*<<< orphan*/  optional_tags_init () ; 
 int order ; 
 int /*<<< orphan*/ * random_rating ; 
 int /*<<< orphan*/  tbl_relevance_init () ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int,int) ; 

__attribute__((used)) static void init_order (void) {
  Q_type = Q_order & 0xff;
  order = (Q_order & FLAG_REVERSE_SEARCH) ? 2 : 1;
  vkprintf (3, "Q_order = %d, Q_type = %d, order = %d\n", Q_order, Q_type, order);
  evaluate_rating = NULL;
  if (Q_type == MAX_RATES + 2) {
    tbl_relevance_init ();
    optional_tags_init ();
    evaluate_rating = evaluate_relevance_search_rating;
  } else if (Q_type == MAX_RATES + 1) {
    evaluate_rating = random_rating;
  } else if (Q_order & (FLAG_ENTRY_SORT_SEARCH | FLAG_PRIORITY_SORT_SEARCH)) {
    if (Q_type == MAX_RATES) {
      evaluate_rating = mix_priority_with_object_id;
    } else {
      assert (Q_type <= 15);
      evaluate_rating = mix_priority_with_rating;
    }
  } else if (Q_type == MAX_RATES) {
    evaluate_rating = get_rating_as_object_id;
  } else {
    assert (Q_type <= 15);
    evaluate_rating = get_rating;
  }
}