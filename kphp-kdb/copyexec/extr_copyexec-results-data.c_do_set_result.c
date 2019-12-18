#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lev_copyexec_result_data {int transaction_id; unsigned int result; long long binlog_pos; int /*<<< orphan*/  random_tag; } ;
struct connection {int dummy; } ;
struct TYPE_4__ {long long binlog_pos; int /*<<< orphan*/  random_tag; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 int COPYEXEC_ERR_DISCONNECT ; 
 int COPYEXEC_ERR_OLD_RESULT ; 
 int /*<<< orphan*/  LEV_COPYEXEC_RESULT_DATA ; 
 struct lev_copyexec_result_data* alloc_log_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_host_by_connection (struct connection*) ; 
 int set_result (TYPE_1__*,struct lev_copyexec_result_data*) ; 

int do_set_result (struct connection *c, int transaction_id, unsigned result, long long binlog_pos) {
  host_t *H = get_host_by_connection (c);
  if (H == NULL) {
    return COPYEXEC_ERR_DISCONNECT;
  }

  if (H->binlog_pos >= binlog_pos) {
    return COPYEXEC_ERR_OLD_RESULT;
  }

  struct lev_copyexec_result_data *E = alloc_log_event (LEV_COPYEXEC_RESULT_DATA, sizeof (*E), 0);
  E->random_tag = H->random_tag;
  E->transaction_id = transaction_id;
  E->result = result;
  E->binlog_pos = binlog_pos;
  return set_result (H, E);
}