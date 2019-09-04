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
struct TYPE_5__ {int /*<<< orphan*/  root; int /*<<< orphan*/  transaction_id; int /*<<< orphan*/  volume_id; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_transaction_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lru_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  tot_memory_transactions ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 

__attribute__((used)) static void transaction_free (transaction_t *T) {
  lru_remove (T);
  get_transaction_f (T->volume_id, T->transaction_id, -1);
  free_tree (T->root);
  zfree (T, sizeof (*T));
  tot_memory_transactions--;
}