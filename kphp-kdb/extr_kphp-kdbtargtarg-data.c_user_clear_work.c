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
struct TYPE_3__ {struct company* work; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;
struct company {struct company* next; int /*<<< orphan*/  job; int /*<<< orphan*/  company_name; int /*<<< orphan*/  name_hashes; int /*<<< orphan*/  job_hashes; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_user_hashlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exact_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct company*,int) ; 

__attribute__((used)) static void user_clear_work (user_t *U) {
  struct company *C, *Nx;
  for (C = U->work; C; C = Nx) {
    delete_user_hashlist (U->uid, C->job_hashes);
    delete_user_hashlist (U->uid, C->name_hashes);
    exact_strfree (C->company_name);
    exact_strfree (C->job);
    Nx = C->next;
    zfree (C, sizeof (struct company));
  }
  U->work = 0;
}