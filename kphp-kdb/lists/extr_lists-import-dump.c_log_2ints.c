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
struct lev_generic {long type; long b; long c; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_id ; 
 struct lev_generic* write_alloc (int) ; 

void log_2ints (long type, long arg1, long arg2) {
  struct lev_generic *L = write_alloc (16);
  L->type = type;
  L->a = list_id;
  L->b = arg1;
  L->c = arg2;
}