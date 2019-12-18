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
typedef  union ctl_io {int dummy; } ctl_io ;
struct TYPE_2__ {int /*<<< orphan*/  ctl_pool_ref; } ;
struct tpcl_softc {TYPE_1__ port; } ;

/* Variables and functions */
 union ctl_io* ctl_alloc_io (int /*<<< orphan*/ ) ; 
 struct tpcl_softc tpcl_softc ; 

union ctl_io *
tpcl_alloc_io(void)
{
	struct tpcl_softc *tsoftc = &tpcl_softc;

	return (ctl_alloc_io(tsoftc->port.ctl_pool_ref));
}