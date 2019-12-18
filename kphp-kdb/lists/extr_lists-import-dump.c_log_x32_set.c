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
struct lev_generic {unsigned int a; unsigned int b; unsigned int c; unsigned int d; unsigned int e; unsigned int f; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LEV_LI_SET_ENTRY ; 
 struct lev_generic* write_alloc (int) ; 

void log_x32_set (unsigned l1, unsigned l2, unsigned l3, unsigned e1, unsigned e2, unsigned value, unsigned char flags) {
  struct lev_generic *L = write_alloc (28);
  L->type = LEV_LI_SET_ENTRY + flags;
  L->a = l1;
  L->b = l2;
  L->c = l3;
  L->d = e1;
  L->e = e2;
  L->f = value;
}