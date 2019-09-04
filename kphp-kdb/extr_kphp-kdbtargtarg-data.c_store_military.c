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
struct TYPE_3__ {int uid; struct military* mil; } ;
typedef  TYPE_1__ user_t ;
struct military {int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  unit_id; struct military* next; } ;
struct lev_military {int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  unit_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  q_mil_finish ; 
 int /*<<< orphan*/  q_mil_start ; 
 int /*<<< orphan*/  q_mil_unit ; 
 int /*<<< orphan*/  user_add_field (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct military* zmalloc (int) ; 

__attribute__((used)) static void store_military (user_t *U, struct lev_military *E) {
  int uid = U->uid;
  struct military *M = zmalloc (sizeof (struct military)), **to = &U->mil;
  M->next = *to;
#define CPY(__x,__f) user_add_field (uid, __f, M->__x = E->__x);  
  CPY(unit_id, q_mil_unit);
  CPY(start, q_mil_start);
  CPY(finish, q_mil_finish);
#undef CPY
  *to = M;
}