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
typedef  int /*<<< orphan*/  transaction_t ;

/* Variables and functions */
 int check_transaction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_temp_transaction (int) ; 

int do_check_transaction (int temp_id) {
  transaction_t *T = get_temp_transaction (temp_id);
  if (!T) {
    return 0;
  }
  int res = check_transaction (T);
  return res < 0 ? res : 3;
}