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
struct lev_generic {unsigned int type; unsigned int a; unsigned int b; unsigned int c; } ;

/* Variables and functions */
 unsigned int LEV_LI_SET_ENTRY ; 
 struct lev_generic* write_alloc (int) ; 

void log_11_set (unsigned l, unsigned e, unsigned value, unsigned flags) {
  struct lev_generic *L = write_alloc (16);
  L->type = LEV_LI_SET_ENTRY + flags;
  L->a = l;
  L->b = e;
  L->c = value;
}