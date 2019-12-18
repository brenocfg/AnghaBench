#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int status; int /*<<< orphan*/  transaction_id; } ;
typedef  TYPE_1__ transaction_t ;
typedef  enum transaction_status { ____Placeholder_transaction_status } transaction_status ;

/* Variables and functions */
 int /*<<< orphan*/  incr_status_counter (scalar_t__,int) ; 
 scalar_t__ ts_unset ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transaction_change_status (transaction_t *T, enum transaction_status status) {
  if (T->status == status) {
    vkprintf (1, "transaction_change_status: T->status == status (%d), T->transacion_id: %d\n", status, T->transaction_id);
    return;
  }
  if (T->status != ts_unset) {
    incr_status_counter (T->status, -1);
  }
  T->status = status;
  incr_status_counter (T->status, 1);
}