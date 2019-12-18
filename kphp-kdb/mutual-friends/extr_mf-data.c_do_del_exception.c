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
struct lev_mf_del_exception {int user_id; int friend_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_MF_DEL_EXCEPTION ; 
 struct lev_mf_del_exception* alloc_log_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int del_exception (struct lev_mf_del_exception*) ; 

int do_del_exception (int uid, int fid) {
  struct lev_mf_del_exception *E =
    alloc_log_event (LEV_MF_DEL_EXCEPTION, sizeof (struct lev_mf_del_exception), 0);

  E->user_id = uid;
  E->friend_id = fid;

  return del_exception (E);
}