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
struct lev_online_lite {int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  account_user_online (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_user (int /*<<< orphan*/ ) ; 

void process_user_online_lite (struct lev_online_lite *E) {
  user_t *U = get_user (E->user_id);
  if (U) {
    account_user_online (U);
  }
}