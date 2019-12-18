#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct keep_mc_header {int num; int list_id; } ;
struct connection {TYPE_1__* Tmp; } ;
struct TYPE_3__ {scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance_read_ptr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int read_in (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  userlist ; 

int get_saved_userlist (struct connection *c, int list_id) {
  if (!c->Tmp) {
    return -1;
  }
  struct keep_mc_header *D = (struct keep_mc_header *) c->Tmp->start;
  advance_read_ptr (c->Tmp, sizeof (struct keep_mc_header));
  int res = D->num;
  assert (read_in (c->Tmp, userlist, res * 4) == 4 * res);
  if (D->list_id != list_id) {
    return -1;
  }
  return res;
}