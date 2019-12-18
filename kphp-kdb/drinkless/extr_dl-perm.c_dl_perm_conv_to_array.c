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
struct TYPE_3__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ dl_perm ;

/* Variables and functions */
 int LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_prm_conv_to_array (int /*<<< orphan*/ ,int*,int) ; 

int dl_perm_conv_to_array (dl_perm *p, int *a, int n) {
  dl_prm_conv_to_array (p->v, a, n);
  return LEN (p->v);
}