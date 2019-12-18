#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int prev_user_creations; } ;
typedef  TYPE_1__ user_t ;
struct advert {int* user_list; int ad_id; int prev_user_creations; int users; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ ADF_ON ; 
 TYPE_1__** User ; 
 int /*<<< orphan*/  activate_one_user_ad (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  deactivate_one_user_ad (TYPE_1__*,int) ; 

__attribute__((used)) static void change_ad_userlist (struct advert *A, int old_users, int *old_user_list, int old_prev_user_creations) {
  assert (A && (A->flags && ADF_ON) && A->user_list);
  int ad_id = A->ad_id, prev_user_creations = A->prev_user_creations;
  int *p = A->user_list, *q = old_user_list;
  int x = *p++, y = *q++;
  user_t *U;
  while (1) {
    if (x < y) {
      U = User[x];
      if (U && U->prev_user_creations <= prev_user_creations) {
	activate_one_user_ad (U, ad_id);
      }
      x = *p++;
    } else if (x > y) {
      U = User[y];
      if (U) {
	deactivate_one_user_ad (U, ad_id);
      }
      y = *q++;
    } else if (x == 0x7fffffff) {
      break;
    } else {
      U = User[x];
      if (U && U->prev_user_creations > old_prev_user_creations && U->prev_user_creations <= prev_user_creations) {
	activate_one_user_ad (U, ad_id);
      }
      x = *p++;
      y = *q++;
    }
  }
  assert (q == old_user_list + old_users + 1 && p == A->user_list + A->users + 1);
}