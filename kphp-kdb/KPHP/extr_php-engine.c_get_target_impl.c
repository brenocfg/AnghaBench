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
struct conn_target {int dummy; } ;

/* Variables and functions */
 int Targets ; 
 struct conn_target* create_target (struct conn_target*,int /*<<< orphan*/ *) ; 

int get_target_impl (struct conn_target *ct) {
  //TODO: fix ref_cnt overflow
  struct conn_target *res = create_target (ct, NULL);
  int res_id = (int)(res - Targets);
  return res_id;
}