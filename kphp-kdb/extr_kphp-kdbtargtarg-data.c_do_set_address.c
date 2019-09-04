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
typedef  int /*<<< orphan*/  user_t ;
struct lev_address_extended {int* text; int /*<<< orphan*/  street; int /*<<< orphan*/  station; int /*<<< orphan*/  district; int /*<<< orphan*/  city; int /*<<< orphan*/  country; int /*<<< orphan*/  atype; } ;
struct address {int /*<<< orphan*/  name; int /*<<< orphan*/  house; int /*<<< orphan*/  street; int /*<<< orphan*/  station; int /*<<< orphan*/  district; int /*<<< orphan*/  city; int /*<<< orphan*/  country; int /*<<< orphan*/  atype; } ;

/* Variables and functions */
 scalar_t__ LEV_TARG_ADDR_EXT_ADD ; 
 struct lev_address_extended* alloc_log_event (scalar_t__,int,int) ; 
 int /*<<< orphan*/  filter_simple_text (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * get_user (int) ; 
 int /*<<< orphan*/  store_address (int /*<<< orphan*/ *,struct lev_address_extended*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int do_set_address (int user_id, struct address *A) {
  user_t *U = get_user (user_id);
  if (!U) {
    return 0;
  }

  int len1 = A->house ? strlen (A->house) : 0;
  int len2 = A->name ? strlen (A->name) : 0;

  if (len1 + len2 + 1 >= 256) { 
    return 0; 
  }

  struct lev_address_extended *E = alloc_log_event (LEV_TARG_ADDR_EXT_ADD + (len1 + len2 + 1),
    (len1 + len2 + 1) + 27, user_id);

#define CPY(__x) E->__x = A->__x;  
  CPY(atype);
  CPY(country);
  CPY(city);
  CPY(district);
  CPY(station);
  CPY(street);
#undef CPY

  if (len1) {
    filter_simple_text (E->text, A->house, len1);
  }
  E->text[len1] = 9;
  if (len2) {
    filter_simple_text (E->text + len1 + 1, A->name, len2);
  }
  E->text[len1 + len2 + 1] = 0;
  store_address (U, E, len1 + len2 + 1);
  return 1;
}