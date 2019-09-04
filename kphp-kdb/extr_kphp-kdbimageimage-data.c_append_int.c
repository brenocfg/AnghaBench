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
struct forth_output {int l; scalar_t__ s; } ;

/* Variables and functions */
 int snprintf (scalar_t__,int,char*,int) ; 

__attribute__((used)) static void append_int (struct forth_output *O, int i) {
  if (O == NULL) { return; }
  int o = (sizeof (O->s) - O->l) - 2;
  if (o <= 0) { return; }
  int sz = snprintf (O->s + O->l, o, "%d\n", i);
  if (sz < 0 || sz >= o) { return; }
  O->l += sz;
}