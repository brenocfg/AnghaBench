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
struct lev_copyexec_result_data {scalar_t__ random_tag; scalar_t__ binlog_pos; int /*<<< orphan*/  result; int /*<<< orphan*/  transaction_id; } ;
struct TYPE_5__ {scalar_t__ random_tag; scalar_t__ binlog_pos; void* last_action_time; void* last_data_time; void* first_data_time; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* get_host_by_random_tag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  log_cur_pos () ; 
 void* now ; 
 int transaction_set_result (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_result (host_t *H, struct lev_copyexec_result_data *E) {
  if (H == NULL) {
    H = get_host_by_random_tag (E->random_tag, 0);
    if (H == NULL) {
      kprintf ("set_result: get_host_by_random_tag (0x%llx) returns NULL. (log_cur_pos: %lld)\n", E->random_tag, log_cur_pos ());
      exit (1);
    }
  }
  assert (H->random_tag == E->random_tag);
  if (H->binlog_pos >= E->binlog_pos) {
    kprintf ("set_result: H->binlog_pos >= E->binlog_pos, H->binlog_pos = 0x%llx, E->binlog_pos = 0x%llx. (log_cur_pos: %lld)\n", H->binlog_pos, E->binlog_pos, log_cur_pos ());
    exit (1);
    return -1;
  }
  H->binlog_pos = E->binlog_pos;
  if (!H->first_data_time) {
    H->first_data_time = now;
  }
  H->last_data_time = H->last_action_time = now;
  return transaction_set_result (H, E->transaction_id, E->result);
}