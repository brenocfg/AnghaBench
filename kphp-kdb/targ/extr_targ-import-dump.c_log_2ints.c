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
struct lev_user_generic {long type; long a; long b; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  user_id ; 
 struct lev_user_generic* write_alloc (int) ; 

void log_2ints (long type, long arg1, long arg2) {
  struct lev_user_generic *L = write_alloc (16);
  L->type = type;
  L->user_id = user_id;
  L->a = arg1;
  L->b = arg2;
}