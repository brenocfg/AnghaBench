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
 scalar_t__ R_cnt ; 
 int R_position ; 
 scalar_t__ R_tot ; 
 int /*<<< orphan*/  postprocess_res ; 
 int /*<<< orphan*/  postprocess_res_std ; 
 int /*<<< orphan*/  store_res ; 
 int /*<<< orphan*/  store_res_std ; 

void clear_res (void) {
  R_cnt = R_tot = 0;
  if (R_position != (-1 << 31)) {
    store_res = store_res_std;
    postprocess_res = postprocess_res_std;
  }
}