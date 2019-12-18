#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_set_rxfilter (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vmxnet3_promisc_set(if_ctx_t ctx, int flags)
{

	vmxnet3_set_rxfilter(iflib_get_softc(ctx), flags);

	return (0);
}