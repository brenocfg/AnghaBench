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
struct TYPE_3__ {scalar_t__ privacy; } ;
typedef  TYPE_1__ user_t ;
struct lev_generic {scalar_t__ b; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 scalar_t__ MAX_PRIVACY ; 
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 

int set_privacy (struct lev_generic *E) {
  user_t *U = get_user (E->a);
  if (!U || E->b < 0 || E->b > MAX_PRIVACY) { return 0; }
  U->privacy = E->b;
  return 1;
}