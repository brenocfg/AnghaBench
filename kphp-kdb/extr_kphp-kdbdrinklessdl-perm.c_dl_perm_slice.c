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
 scalar_t__ LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dl_prm_slice (int /*<<< orphan*/ ,int*,int,int) ; 
 int max (scalar_t__,int /*<<< orphan*/ ) ; 

int dl_perm_slice (dl_perm *p, int *a, int n, int offset) {
  if (offset < 0) {
    offset = 0;
  }
  dl_prm_slice (p->v, a, n, offset);
  return max (LEN (p->v) - offset, 0);
}