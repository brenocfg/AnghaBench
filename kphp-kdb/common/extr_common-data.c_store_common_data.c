#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ uinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  updated_at; } ;

/* Variables and functions */
 TYPE_1__ CDataUserInfo ; 
 TYPE_2__* MyCData ; 
 int /*<<< orphan*/  get_precise_time (int) ; 
 int /*<<< orphan*/  update_user_info_copy (scalar_t__,TYPE_1__*) ; 

int store_common_data (void) {
  if (!MyCData) {
    return -1;
  }
  CDataUserInfo.updated_at = get_precise_time (1000000);
  update_user_info_copy (MyCData->uinfo, &CDataUserInfo);
  update_user_info_copy (MyCData->uinfo + 1, &CDataUserInfo);
  return 1;
}