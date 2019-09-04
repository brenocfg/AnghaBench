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
struct lev_company {int* text; int /*<<< orphan*/  country; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  company; int /*<<< orphan*/  city; } ;
struct company {int /*<<< orphan*/  job; int /*<<< orphan*/  company_name; int /*<<< orphan*/  country; int /*<<< orphan*/  finish; int /*<<< orphan*/  start; int /*<<< orphan*/  company; int /*<<< orphan*/  city; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_COMP_ADD ; 
 struct lev_company* alloc_log_event (scalar_t__,int,int) ; 
 scalar_t__ conv_user_id (int) ; 
 int /*<<< orphan*/  filter_simple_text (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_company (struct lev_company*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int do_set_work (int user_id, struct company *C) {
  int len1 = C->company_name ? strlen (C->company_name) : 0;
  int len2 = C->job ? strlen (C->job) : 0;
  if (len1 + len2 >= 255 || conv_user_id (user_id) < 0) {
    return 0;
  }
  struct lev_company *E = alloc_log_event (LEV_TARG_COMP_ADD + (len1 + len2 + 1),
    len1 + len2 + 23, user_id);

#define CPY(__x) E->__x = C->__x;  
  CPY(city);
  CPY(company);
  CPY(start);
  CPY(finish);
  CPY(country);
#undef CPY

  if (len1) {
    filter_simple_text (E->text, C->company_name, len1);
  }
  E->text[len1] = 9;
  if (len2) {
    filter_simple_text (E->text + len1 + 1, C->job, len2);
  }
  E->text[len1 + len2 + 1] = 0;
  store_company (E, len1 + len2 + 23);
  return 1;
}