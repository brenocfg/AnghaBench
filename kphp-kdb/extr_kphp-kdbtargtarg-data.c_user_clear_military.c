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
struct TYPE_3__ {struct military* mil; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;
struct military {struct military* next; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  unit_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  q_mil_finish ; 
 int /*<<< orphan*/  q_mil_start ; 
 int /*<<< orphan*/  q_mil_unit ; 
 int /*<<< orphan*/  user_clear_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct military*,int) ; 

__attribute__((used)) static void user_clear_military (user_t *U) {
  struct military *M, *Nx;
  for (M = U->mil; M; M = Nx) {
#define DEL(__x,__f) user_clear_field (U->uid, __f, M->__x);  
    DEL(unit_id, q_mil_unit);
    DEL(start, q_mil_start);
    DEL(finish, q_mil_finish);
#undef DEL
    Nx = M->next;
    zfree (M, sizeof (struct military));
  }
  U->mil = 0;
}