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
struct TYPE_3__ {int /*<<< orphan*/  xy2d; int /*<<< orphan*/  yminusx; int /*<<< orphan*/  yplusx; } ;
typedef  TYPE_1__ ge_precomp ;

/* Variables and functions */
 int /*<<< orphan*/  fe_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ge_precomp_0(ge_precomp *h)
{
    fe_1(h->yplusx);
    fe_1(h->yminusx);
    fe_0(h->xy2d);
}