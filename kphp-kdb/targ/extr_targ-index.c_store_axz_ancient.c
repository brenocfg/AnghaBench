#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* intree_t ;
struct TYPE_7__ {int /*<<< orphan*/  view_count; int /*<<< orphan*/  uid; int /*<<< orphan*/  ad_id; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  z; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int ADF_NEWANCIENT ; 
 TYPE_4__* all_stale_ads_userlist_ptr ; 
 TYPE_3__* get_ad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stale_ads_current_user ; 

__attribute__((used)) static int store_axz_ancient (intree_t TC) {
  if (get_ad (TC->x)->flags & ADF_NEWANCIENT) {
    all_stale_ads_userlist_ptr->ad_id = TC->x;
    all_stale_ads_userlist_ptr->uid = stale_ads_current_user;
    all_stale_ads_userlist_ptr->view_count = TC->z;
    ++all_stale_ads_userlist_ptr;
    return 1;
  } else {
    return 0;
  }
}