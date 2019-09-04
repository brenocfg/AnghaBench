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
 int Q_aux_num ; 
 int /*<<< orphan*/  R ; 
 int R_cnt ; 
 int R_position ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int perform_query (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postprocess_res ; 
 int /*<<< orphan*/  postprocess_res_std ; 
 int /*<<< orphan*/  store_res ; 
 int /*<<< orphan*/  store_res_aud ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int perform_audience_query (void) {
  vkprintf (1, "perform audience query() for %d auxiliary queries\n", Q_aux_num);
  memset (R, 0, Q_aux_num * 4);
  R_position = (-1 << 31);
  store_res = store_res_aud;
  postprocess_res = postprocess_res_std;
  int res = perform_query (0);
  R_cnt = Q_aux_num;
  R_position = 0;
  return res;
}