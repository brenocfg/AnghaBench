#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int /*<<< orphan*/  (* ClearLoopingSounds ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ si ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void S_ClearLoopingSounds( qboolean killall )
{
	if( si.ClearLoopingSounds ) {
		si.ClearLoopingSounds( killall );
	}
}