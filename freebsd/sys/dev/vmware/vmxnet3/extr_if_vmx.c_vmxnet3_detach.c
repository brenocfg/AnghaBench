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
struct vmxnet3_softc {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 struct vmxnet3_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_free_data (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_free_irqs (struct vmxnet3_softc*) ; 
 int /*<<< orphan*/  vmxnet3_free_resources (struct vmxnet3_softc*) ; 

__attribute__((used)) static int
vmxnet3_detach(if_ctx_t ctx)
{
	struct vmxnet3_softc *sc;

	sc = iflib_get_softc(ctx);

	vmxnet3_free_irqs(sc);
	vmxnet3_free_data(sc);
	vmxnet3_free_resources(sc);

	return (0);
}