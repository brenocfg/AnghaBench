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
 int /*<<< orphan*/  if_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_set_rxfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_multi_set(if_ctx_t ctx)
{

	vmxnet3_set_rxfilter(iflib_get_softc(ctx),
	    if_getflags(iflib_get_ifp(ctx)));
}