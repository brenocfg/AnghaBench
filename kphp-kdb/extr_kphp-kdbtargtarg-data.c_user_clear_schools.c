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
struct TYPE_3__ {struct school* sch; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;
struct school {struct school* next; int /*<<< orphan*/  spec; int /*<<< orphan*/  spec_hashes; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  country; int /*<<< orphan*/  grad; int /*<<< orphan*/  school; int /*<<< orphan*/  city; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exact_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_sch_city ; 
 int /*<<< orphan*/  q_sch_class ; 
 int /*<<< orphan*/  q_sch_country ; 
 int /*<<< orphan*/  q_sch_grad ; 
 int /*<<< orphan*/  q_sch_id ; 
 int /*<<< orphan*/  user_clear_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct school*,int) ; 

__attribute__((used)) static void user_clear_schools (user_t *U) {
  struct school *S, *Nx;
  for (S = U->sch; S; S = Nx) {
#define DEL(__x,__f) user_clear_field (U->uid, __f, S->__x);  
    DEL(city, q_sch_city);
    DEL(school, q_sch_id);
    DEL(grad, q_sch_grad);
    DEL(country, q_sch_country);
    DEL(sch_class, q_sch_class);
#undef DEL
    delete_user_hashlist (U->uid, S->spec_hashes);
    exact_strfree (S->spec);
    Nx = S->next;
    zfree (S, sizeof (struct school));
  }
  U->sch = 0;
}