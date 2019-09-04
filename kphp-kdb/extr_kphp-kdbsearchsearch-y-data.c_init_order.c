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
 int MAX_RATES ; 
 int Q_order ; 
 int Q_type ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * evaluate_rating ; 
 int /*<<< orphan*/ * get_rating ; 
 int /*<<< orphan*/ * get_rating_as_object_id ; 
 int /*<<< orphan*/ * random_rating ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int) ; 

__attribute__((used)) static void init_order (void) {
  Q_type = Q_order & 0xff;
  vkprintf (3, "Q_order = %d, Q_type = %d\n", Q_order, Q_type);
  evaluate_rating = NULL;
  if (Q_type == MAX_RATES + 1) {
    evaluate_rating = random_rating;
  } else if (Q_type == MAX_RATES) {
    evaluate_rating = get_rating_as_object_id;
  } else {
    assert (Q_type <= 15);
    evaluate_rating = get_rating;
  }
}