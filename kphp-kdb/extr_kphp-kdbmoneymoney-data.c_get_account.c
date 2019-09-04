#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {long long acc_id; TYPE_1__* acc_type; struct TYPE_6__* h_next; } ;
typedef  TYPE_2__ account_t ;
struct TYPE_5__ {int acc_type_id; } ;

/* Variables and functions */
 TYPE_2__** AccHash ; 
 int account_bucket (int,long long) ; 

account_t *get_account (int acc_type_id, long long acc_id) {
  int b = account_bucket (acc_type_id, acc_id);
  account_t *ptr;

  for (ptr = AccHash[b]; ptr; ptr = ptr->h_next) {
    if (acc_id == ptr->acc_id && acc_type_id == ptr->acc_type->acc_type_id) {
      return ptr;
    }
  }
  return 0;
}