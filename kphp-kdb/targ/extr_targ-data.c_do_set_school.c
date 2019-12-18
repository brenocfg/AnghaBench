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
struct school {int /*<<< orphan*/  spec; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  country; int /*<<< orphan*/  grad; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  school; int /*<<< orphan*/  city; } ;
struct lev_school {scalar_t__* spec; int /*<<< orphan*/  sch_type; int /*<<< orphan*/  sch_class; int /*<<< orphan*/  country; int /*<<< orphan*/  grad; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  school; int /*<<< orphan*/  city; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_SCH_ADD ; 
 struct lev_school* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_user_id (int) ; 
 int /*<<< orphan*/  filter_simple_text (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_school (struct lev_school*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int do_set_school (int user_id, struct school *S) {
  int len = S->spec ? strlen (S->spec) : 0;
  if (len >= 256 || conv_user_id (user_id) < 0) {
    return 0;
  }
  struct lev_school *E = alloc_log_event (LEV_TARG_SCH_ADD + len, 26 + len, user_id);
  E->city = S->city;
  E->school = S->school;
  E->start = S->start;
  E->finish = S->finish;
  E->grad = S->grad;
  E->country = S->country;
  E->sch_class = S->sch_class;
  E->sch_type = S->sch_type;
  if (len) {
    filter_simple_text (E->spec, S->spec, len);
  }
  E->spec[len] = 0;
  store_school (E, 26+len);
  return 1;
}