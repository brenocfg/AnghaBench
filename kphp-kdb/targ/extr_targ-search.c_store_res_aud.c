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

/* Variables and functions */
 int /*<<< orphan*/ * AuxCond ; 
 int Q_aux_num ; 
 int /*<<< orphan*/ * R ; 
 int /*<<< orphan*/  R_tot ; 
 int /*<<< orphan*/ * User ; 
 scalar_t__ user_matches_condition (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

void store_res_aud (int uid) {
  long i;
  vkprintf (3, "store_res_aud(%d)\n", uid);
  for (i = 0; (int) i < Q_aux_num; i++) {
    if (user_matches_condition (User[uid], AuxCond[i], uid)) {
      R[i]++;
    }
  }
  R_tot++;
}