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
struct msg {int run_set; int run_length; struct msg* run_data; scalar_t__ run_num_allocated; int /*<<< orphan*/ * attack_data; struct msg* to_name_data; struct msg* from_name_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct msg*) ; 
 int /*<<< orphan*/  kill_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_free (struct msg) ; 

void
msg_free(struct msg *tmp)
{
  if (tmp->from_name_data != NULL)
      free (tmp->from_name_data);
  if (tmp->to_name_data != NULL)
      free (tmp->to_name_data);
  if (tmp->attack_data != NULL)
      kill_free(tmp->attack_data);
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
  free(tmp->run_data);
  free(tmp);
}