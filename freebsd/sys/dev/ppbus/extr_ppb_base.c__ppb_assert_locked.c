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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  ppc_lock; } ;

/* Variables and functions */
 TYPE_1__* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

void
_ppb_assert_locked(device_t bus, const char *file, int line)
{

	mtx_assert_(DEVTOSOFTC(bus)->ppc_lock, MA_OWNED, file, line);
}