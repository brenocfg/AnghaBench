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
struct TYPE_6__ {int place; } ;
typedef  TYPE_1__ place_t ;
typedef  int /*<<< orphan*/  notify_place_t ;

/* Variables and functions */
 scalar_t__ COMM_MODE ; 
 scalar_t__ NOTIFY_MODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_obj (int,int,int) ; 
 int /*<<< orphan*/  free_comment_list (TYPE_1__*) ; 
 int /*<<< orphan*/  free_notify_place_list (int /*<<< orphan*/ *) ; 
 TYPE_1__* get_place_f (int,int,int,int) ; 
 scalar_t__ min_logevent_time ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  tot_places ; 
 int /*<<< orphan*/  vkprintf (int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 

__attribute__((used)) static int delete_place (int type, int owner, int place) {
  if (now < min_logevent_time) {
    return 0;
  }
  if (!check_obj (type, owner, place)) {
    return -1;
  }
  place_t *V = get_place_f (type, owner, place, -1);
  vkprintf (2, "delete_place: V = %p\n", V);
  if (!V) {
    return 0;
  }

  assert (COMM_MODE || NOTIFY_MODE);
  if (COMM_MODE) {
    free_comment_list (V);
    V->place = -1;
    zfree (V, sizeof (place_t));
  } else {
    free_notify_place_list ((notify_place_t *)V);
    V->place = -1;
    zfree (V, sizeof (notify_place_t));
  }
  tot_places--;
  return 1;
}