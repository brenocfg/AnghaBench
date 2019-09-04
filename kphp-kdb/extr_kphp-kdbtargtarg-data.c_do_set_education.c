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
struct TYPE_3__ {int /*<<< orphan*/  edu; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;
struct lev_education {int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; int /*<<< orphan*/  country; int /*<<< orphan*/  city; int /*<<< orphan*/  university; int /*<<< orphan*/  faculty; int /*<<< orphan*/  chair; int /*<<< orphan*/  grad_year; } ;
struct education {int /*<<< orphan*/  edu_status; int /*<<< orphan*/  edu_form; int /*<<< orphan*/  country; int /*<<< orphan*/  city; int /*<<< orphan*/  university; int /*<<< orphan*/  faculty; int /*<<< orphan*/  chair; int /*<<< orphan*/  grad_year; int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_EDUADD ; 
 struct lev_education* alloc_log_event (scalar_t__,int,int) ; 
 TYPE_1__* get_user (int) ; 
 int /*<<< orphan*/  store_edu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct lev_education*) ; 

int do_set_education (int user_id, struct education *E) {
  user_t *U = get_user (user_id);
  if (!U) {
    return 0;
  }

  struct lev_education *D = alloc_log_event (
    LEV_TARG_EDUADD + !!E->primary, sizeof (struct lev_education), user_id
  );

#define CPY(__x) D->__x = E->__x;  
  CPY(grad_year);
  CPY(chair);
  CPY(faculty);
  CPY(university);
  CPY(city);
  CPY(country);
  CPY(edu_form);
  CPY(edu_status);
#undef CPY
  store_edu (U->uid, &U->edu, D);
  return 1;
}