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
typedef  int /*<<< orphan*/  user_t ;

/* Variables and functions */
 int /*<<< orphan*/  update_history (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  update_history_persistent (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void update_history_both (user_t *U, int local_id, int flags, int op) {
  if ((unsigned) op <= 5) {
    update_history_persistent (U, local_id, flags, op);
  }
  update_history (U, local_id, flags, op);
}