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
struct account {struct account* h_next; int /*<<< orphan*/  acc_id; TYPE_1__* acc_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  acc_type_id; } ;

/* Variables and functions */
 struct account** AccHash ; 
 int account_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_account (struct account *A) {
  int b = account_bucket (A->acc_type->acc_type_id, A->acc_id);

  A->h_next = AccHash[b];
  AccHash[b] = A;
  return 0;
}