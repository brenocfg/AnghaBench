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
 int /*<<< orphan*/  dl_prm_free (int /*<<< orphan*/ ) ; 

void dl_perm_free (dl_perm *p) {
  dl_prm_free (p->v);
}