#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int value; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_8__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_2__ transaction_t ;
struct TYPE_9__ {int /*<<< orphan*/  host_id; int /*<<< orphan*/  volume_id; } ;
typedef  TYPE_3__ host_t ;

/* Variables and functions */
 TYPE_2__* get_transaction_f (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transaction_set_result (host_t *H, int transaction_id, unsigned result) {
  transaction_t *T = get_transaction_f (H->volume_id, transaction_id, 1);
  tree_t *P = tree_lookup (T->root, H->host_id);
  if (P != NULL) {
    P->value = result;
  } else {
    T->root = tree_insert (T->root, H->host_id, lrand48 (), result);
  }
  return 0;
}