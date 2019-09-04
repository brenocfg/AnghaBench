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
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int GET_USER_RATING_STATE (int /*<<< orphan*/ ) ; 
 int rating_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * user_get_object_rating (TYPE_1__*,int,int) ; 
 long long user_get_object_type_id (TYPE_1__*,int) ; 

int object_cmp (user *u, int a, int b, int num) {
  int x = 0;
  if (GET_USER_RATING_STATE(u->flags) == 1) {
    x = rating_cmp (*user_get_object_rating (u, a, num), *user_get_object_rating (u, b, num));
  }
  if (x != 0) {
    return x;
  }

  // TODO optimize if needed
  long long a1 = user_get_object_type_id (u, a);
  long long b1 = user_get_object_type_id (u, b);

  if (a1 < b1) {
    return 1;
  } else if (a1 > b1) {
    return -1;
  }

  return 0;
}