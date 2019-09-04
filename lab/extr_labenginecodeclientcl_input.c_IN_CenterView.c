#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * delta_angles; } ;
struct TYPE_5__ {TYPE_1__ ps; } ;
struct TYPE_6__ {TYPE_2__ snap; int /*<<< orphan*/ * viewangles; } ;

/* Variables and functions */
 size_t PITCH ; 
 int /*<<< orphan*/  SHORT2ANGLE (int /*<<< orphan*/ ) ; 
 TYPE_3__ cl ; 

void IN_CenterView (void) {
	cl.viewangles[PITCH] = -SHORT2ANGLE(cl.snap.ps.delta_angles[PITCH]);
}