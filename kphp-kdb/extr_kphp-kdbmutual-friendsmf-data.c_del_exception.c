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
struct TYPE_3__ {int /*<<< orphan*/  new_exceptions; } ;
typedef  TYPE_1__ user ;
struct lev_mf_del_exception {int friend_id; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  chg_del (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* conv_uid (int /*<<< orphan*/ ) ; 
 int expired_aio_queries ; 

int del_exception (struct lev_mf_del_exception *E) {
  user *u = conv_uid (E->user_id);

  if (u == NULL) {
    return 0;
  }

  if (1 <= E->friend_id && E->friend_id < 500000000) {
    chg_del (&u->new_exceptions, 2 * E->friend_id + 1);
  } else {
//    fprintf (stderr, "WARNING: del exceptions %d %d\n", E->user_id, E->friend_id);
    expired_aio_queries += 100;
  }

  return 1;
}