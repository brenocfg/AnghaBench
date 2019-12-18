#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  transaction_t ;
struct TYPE_2__ {int /*<<< orphan*/ * th_last; int /*<<< orphan*/ * th_first; } ;

/* Variables and functions */
 int TRANS_TEMP_HASH_SIZE ; 
 TYPE_1__* TrTempHash ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  money_replay_logevent ; 
 int /*<<< orphan*/  replay_logevent ; 
 int /*<<< orphan*/  tot_account_types ; 
 int /*<<< orphan*/  tot_accounts ; 
 int /*<<< orphan*/  tot_transactions ; 

int init_money_data (int schema) {
  int i;

  replay_logevent = money_replay_logevent;

  assert (!tot_account_types && !tot_accounts && !tot_transactions);

  for (i = 0; i < TRANS_TEMP_HASH_SIZE; i++) {
    TrTempHash[i].th_first = TrTempHash[i].th_last = (transaction_t *) &TrTempHash[i];
  }

  return 0;
}