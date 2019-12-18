#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ proposal; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int /*<<< orphan*/  store_proposal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int user_clear_proposal (user_t *U) {
  int res = (U->proposal != 0);
  store_proposal (U, 0, 0);
  return res;
}