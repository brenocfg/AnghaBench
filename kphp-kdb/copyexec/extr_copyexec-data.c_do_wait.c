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
 int /*<<< orphan*/ * get_transaction_f (int,int /*<<< orphan*/ ) ; 
 int transaction_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_wait (int transaction_id) {
  transaction_t *T = get_transaction_f (transaction_id, 0);
  if (T == NULL) {
    return 0;
  }
  return transaction_wait (T);
}