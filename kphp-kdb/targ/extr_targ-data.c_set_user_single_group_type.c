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
struct TYPE_3__ {int* user_group_types; } ;
typedef  TYPE_1__ user_t ;
struct lev_generic {int type; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_user_single_group_type (struct lev_generic *E) {
  user_t *U = get_user (E->a);
  if (!U) {
    return 0;
  }
  unsigned type = E->type & 0x7f;
  U->user_group_types[type >> 5] |= (1 << (type & 31));
  return 1;
}