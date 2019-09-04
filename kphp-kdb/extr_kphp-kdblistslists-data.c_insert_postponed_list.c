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
struct lev_generic {int dummy; } ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int find_metafile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_postponed (int,struct lev_generic*,int) ; 
 int log_event_size (struct lev_generic*) ; 

int insert_postponed_list (list_id_t list_id, struct lev_generic *E) {
  int x = find_metafile (list_id);
  assert (x >= 0);
  /*if (x < 0) {
    return 0;
  }*/
  int size = log_event_size (E);
  insert_postponed (x, E, size);
  return 1;
}