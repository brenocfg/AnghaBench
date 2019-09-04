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
typedef  int /*<<< orphan*/  user_t ;
typedef  TYPE_1__* condition_t ;
struct TYPE_4__ {int (* eval ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

inline int user_matches_condition (user_t *U, condition_t C, int uid) {
  return C->eval (C, U, 0, uid);
}