#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* ccb_p ;
struct TYPE_7__ {TYPE_2__* cam_ccb; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
struct TYPE_6__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_print_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PRINT_ADDR (ccb_p cp)
{
	if (cp && cp->cam_ccb)
		xpt_print_path(cp->cam_ccb->ccb_h.path);
}