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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* UpdateEntityPosition ) (int,int /*<<< orphan*/  const) ;} ;

/* Variables and functions */
 TYPE_1__ si ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/  const) ; 

void S_UpdateEntityPosition( int entityNum, const vec3_t origin )
{
	if( si.UpdateEntityPosition ) {
		si.UpdateEntityPosition( entityNum, origin );
	}
}