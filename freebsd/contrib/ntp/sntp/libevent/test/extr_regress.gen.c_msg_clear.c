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
struct msg {int from_name_set; int to_name_set; int attack_set; int run_set; int run_length; scalar_t__ run_num_allocated; int /*<<< orphan*/ * run_data; int /*<<< orphan*/ * attack_data; int /*<<< orphan*/ * to_name_data; int /*<<< orphan*/ * from_name_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_free (int /*<<< orphan*/ ) ; 

void
msg_clear(struct msg *tmp)
{
  if (tmp->from_name_set == 1) {
    free(tmp->from_name_data);
    tmp->from_name_data = NULL;
    tmp->from_name_set = 0;
  }
  if (tmp->to_name_set == 1) {
    free(tmp->to_name_data);
    tmp->to_name_data = NULL;
    tmp->to_name_set = 0;
  }
  if (tmp->attack_set == 1) {
    kill_free(tmp->attack_data);
    tmp->attack_data = NULL;
    tmp->attack_set = 0;
  }
  if (tmp->run_set == 1) {
    int i;
    for (i = 0; i < tmp->run_length; ++i) {
      run_free(tmp->run_data[i]);
    }
    free(tmp->run_data);
    tmp->run_data = NULL;
    tmp->run_set = 0;
    tmp->run_length = 0;
    tmp->run_num_allocated = 0;
  }
}