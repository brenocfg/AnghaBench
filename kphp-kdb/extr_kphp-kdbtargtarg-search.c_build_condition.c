#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct condition_basic {int dummy; } ;
struct TYPE_11__ {int flags; int type; int /*<<< orphan*/  value; struct TYPE_11__* left; struct TYPE_11__* right; } ;
typedef  TYPE_1__ query_t ;
typedef  TYPE_2__* condition_t ;
typedef  void* condition_func_t ;
struct TYPE_12__ {struct TYPE_12__* true_branch; struct TYPE_12__* false_branch; void* eval; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILE_COND_EQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPILE_COND_RANGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPILE_COND_TWOWORDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPILE_COND_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPILE_COND_WORD_NOSTEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPILE_QUANTIFIER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  address ; 
 int /*<<< orphan*/  adr_city ; 
 int /*<<< orphan*/  adr_country ; 
 int /*<<< orphan*/  adr_district ; 
 int /*<<< orphan*/  adr_house ; 
 int /*<<< orphan*/  adr_name ; 
 int /*<<< orphan*/  adr_station ; 
 int /*<<< orphan*/  adr_street ; 
 int /*<<< orphan*/  adr_type ; 
 int /*<<< orphan*/  age ; 
 int /*<<< orphan*/  alcohol ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bday ; 
 int /*<<< orphan*/  birthday_soon ; 
 int /*<<< orphan*/  bmonth ; 
 int /*<<< orphan*/  browser ; 
 int /*<<< orphan*/  byear ; 
 int /*<<< orphan*/  chair ; 
 int /*<<< orphan*/  city ; 
 int /*<<< orphan*/  company ; 
 int /*<<< orphan*/  company_name ; 
 TYPE_2__* compile_condition_inlist (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  country ; 
 int /*<<< orphan*/  custom1 ; 
 int /*<<< orphan*/  custom10 ; 
 int /*<<< orphan*/  custom11 ; 
 int /*<<< orphan*/  custom12 ; 
 int /*<<< orphan*/  custom13 ; 
 int /*<<< orphan*/  custom14 ; 
 int /*<<< orphan*/  custom15 ; 
 int /*<<< orphan*/  custom2 ; 
 int /*<<< orphan*/  custom3 ; 
 int /*<<< orphan*/  custom4 ; 
 int /*<<< orphan*/  custom5 ; 
 int /*<<< orphan*/  custom6 ; 
 int /*<<< orphan*/  custom7 ; 
 int /*<<< orphan*/  custom8 ; 
 int /*<<< orphan*/  custom9 ; 
 int /*<<< orphan*/  cvisited ; 
 int /*<<< orphan*/  edu_form ; 
 int /*<<< orphan*/  edu_status ; 
 int /*<<< orphan*/  education ; 
 int /*<<< orphan*/  faculty ; 
 int /*<<< orphan*/  future_age ; 
 int /*<<< orphan*/  gcountry ; 
 int /*<<< orphan*/  graduation ; 
 int /*<<< orphan*/  grp_id ; 
 int /*<<< orphan*/  grp_type ; 
 int /*<<< orphan*/  has_photo ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  hidden ; 
 int /*<<< orphan*/  hometown ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  iiothers ; 
 int /*<<< orphan*/  interests ; 
 int /*<<< orphan*/  job ; 
 int /*<<< orphan*/  lang_id ; 
 int /*<<< orphan*/  mil_finish ; 
 int /*<<< orphan*/  mil_start ; 
 int /*<<< orphan*/  mil_unit ; 
 int /*<<< orphan*/  military ; 
 int /*<<< orphan*/  mstatus ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  name_interests ; 
 int /*<<< orphan*/  online ; 
 int /*<<< orphan*/  operator ; 
 int /*<<< orphan*/  pays_money ; 
 int /*<<< orphan*/  political ; 
 int /*<<< orphan*/  ppriority ; 
 int /*<<< orphan*/  privacy ; 
 int /*<<< orphan*/  proposal ; 
#define  q_and 135 
#define  q_birthday_today 134 
#define  q_birthday_tomorrow 133 
#define  q_false 132 
#define  q_inlist 131 
#define  q_not 130 
#define  q_or 129 
#define  q_true 128 
 int /*<<< orphan*/  random ; 
 int /*<<< orphan*/  region ; 
 int /*<<< orphan*/  religion ; 
 int /*<<< orphan*/  sch_city ; 
 int /*<<< orphan*/  sch_class ; 
 int /*<<< orphan*/  sch_country ; 
 int /*<<< orphan*/  sch_grad ; 
 int /*<<< orphan*/  sch_id ; 
 int /*<<< orphan*/  sch_spec ; 
 int /*<<< orphan*/  school ; 
 int /*<<< orphan*/  sex ; 
 int /*<<< orphan*/  smoking ; 
 int /*<<< orphan*/  timezone ; 
 int /*<<< orphan*/  uni_city ; 
 int /*<<< orphan*/  uni_country ; 
 int /*<<< orphan*/  univ ; 
 int /*<<< orphan*/  uses_apps ; 
 TYPE_2__* zmalloc (int) ; 

condition_t build_condition (query_t *Q, condition_t true_branch, condition_t false_branch, int opt_level) {
  if (Q->flags & 1) {
    condition_t tmp = true_branch;
    true_branch = false_branch;
    false_branch = tmp;
  }
  if (Q->flags & 2) {
    condition_func_t quantifier_first, quantifier_next;
    switch (Q->type) {
      COMPILE_QUANTIFIER (education);
      COMPILE_QUANTIFIER (military);
      COMPILE_QUANTIFIER (address);
      COMPILE_QUANTIFIER (company);
      COMPILE_QUANTIFIER (school);
    default:
      assert (0);
    }
    condition_t A = zmalloc (sizeof (struct condition_basic));
    condition_t B = zmalloc (sizeof (struct condition_basic));
    A->eval = quantifier_first;
    B->eval = quantifier_next;
    A->false_branch = B->false_branch = false_branch;
    A->true_branch = B->true_branch = build_condition (Q->left, true_branch, B, opt_level);
    return A;
  }

  switch (Q->type) {
  case q_and:
    return build_condition (Q->left, build_condition (Q->right, true_branch, false_branch, opt_level), false_branch, opt_level);
  case q_or:
    return build_condition (Q->left, true_branch, build_condition (Q->right, true_branch, false_branch, opt_level), opt_level);
  case q_not:
    return build_condition (Q->left, false_branch, true_branch, opt_level);
  case q_false:
    return false_branch;
  case q_true:
    return true_branch;
  case q_inlist:
    return compile_condition_inlist (true_branch, false_branch, opt_level);
  case q_birthday_today:
  case q_birthday_tomorrow:
    Q->value = Q->type - q_birthday_today;
    COMPILE_COND_EQ (birthday_soon);

    COMPILE_COND_RANGE (random);
    COMPILE_COND_RANGE (id);
    COMPILE_COND_EQ (country);
    COMPILE_COND_EQ (city);
    COMPILE_COND_RANGE (bday);
    COMPILE_COND_RANGE (bmonth);
    COMPILE_COND_RANGE (byear);
    COMPILE_COND_RANGE (age);
    COMPILE_COND_RANGE (future_age);
    COMPILE_COND_EQ (political);
    COMPILE_COND_EQ (sex);
    COMPILE_COND_EQ (operator);
    COMPILE_COND_RANGE (browser);
    COMPILE_COND_EQ (region);
    COMPILE_COND_RANGE (height);
    COMPILE_COND_EQ (smoking);
    COMPILE_COND_EQ (alcohol);
    COMPILE_COND_EQ (ppriority);
    COMPILE_COND_EQ (iiothers);
    COMPILE_COND_RANGE (hidden);
    COMPILE_COND_RANGE (cvisited);
    COMPILE_COND_EQ (gcountry);
    COMPILE_COND_RANGE (custom1);
    COMPILE_COND_RANGE (custom2);
    COMPILE_COND_RANGE (custom3);
    COMPILE_COND_RANGE (custom4);
    COMPILE_COND_RANGE (custom5);
    COMPILE_COND_RANGE (custom6);
    COMPILE_COND_RANGE (custom7);
    COMPILE_COND_RANGE (custom8);
    COMPILE_COND_RANGE (custom9);
    COMPILE_COND_RANGE (custom10);
    COMPILE_COND_RANGE (custom11);
    COMPILE_COND_RANGE (custom12);
    COMPILE_COND_RANGE (custom13);
    COMPILE_COND_RANGE (custom14);
    COMPILE_COND_RANGE (custom15);
    COMPILE_COND_RANGE (timezone);
    COMPILE_COND_EQ (mstatus);
    COMPILE_COND_EQ (grp_type);  
    COMPILE_COND_EQ (grp_id);
    COMPILE_COND_EQ (lang_id);
    COMPILE_COND_WORD_NOSTEM (name);
    COMPILE_COND_WORD (interests);
    COMPILE_COND_TWOWORDS (name_interests);
    COMPILE_COND_WORD (religion);
    COMPILE_COND_WORD (hometown);
    COMPILE_COND_WORD (proposal);
    COMPILE_COND_RANGE (online);
    COMPILE_COND_EQ (privacy);
    COMPILE_COND_EQ (has_photo);
    COMPILE_COND_EQ (uses_apps);
    COMPILE_COND_EQ (pays_money);

    COMPILE_COND_EQ (uni_country);
    COMPILE_COND_EQ (uni_city);
    COMPILE_COND_EQ (univ);
    COMPILE_COND_EQ (faculty);
    COMPILE_COND_EQ (chair);
    COMPILE_COND_RANGE (graduation);
    COMPILE_COND_EQ (edu_form);
    COMPILE_COND_EQ (edu_status);

    COMPILE_COND_EQ (mil_unit);
    COMPILE_COND_RANGE (mil_start);
    COMPILE_COND_RANGE (mil_finish);

    COMPILE_COND_EQ (adr_country);
    COMPILE_COND_EQ (adr_city);
    COMPILE_COND_EQ (adr_district);
    COMPILE_COND_EQ (adr_station);
    COMPILE_COND_EQ (adr_street);
    COMPILE_COND_EQ (adr_type);
    COMPILE_COND_WORD (adr_house);
    COMPILE_COND_WORD (adr_name);

    COMPILE_COND_WORD (job);
    COMPILE_COND_WORD (company_name);

    COMPILE_COND_EQ (sch_country);
    COMPILE_COND_EQ (sch_city);
    COMPILE_COND_EQ (sch_id);
    COMPILE_COND_RANGE (sch_grad);
    COMPILE_COND_EQ (sch_class);
    COMPILE_COND_WORD (sch_spec);

  default:
    assert (0);
  }
}