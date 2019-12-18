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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 TYPE_1__ opalcons_buffer ; 
 int /*<<< orphan*/  pmap_bootstrapped ; 

__attribute__((used)) static void
uart_opal_real_unmap_outbuffer(uint64_t *len)
{

	if (!pmap_bootstrapped)
		return;

	mtx_assert(&opalcons_buffer.mtx, MA_OWNED);
	*len = opalcons_buffer.size;
	mtx_unlock_spin(&opalcons_buffer.mtx);
}