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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmxnet3_softc {scalar_t__ vmx_link_active; int /*<<< orphan*/  vmx_ctx; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  iflib_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vmxnet3_link_is_up (struct vmxnet3_softc*) ; 

__attribute__((used)) static void
vmxnet3_link_status(struct vmxnet3_softc *sc)
{
	if_ctx_t ctx;
	uint64_t speed;
	int link;

	ctx = sc->vmx_ctx;
	link = vmxnet3_link_is_up(sc);
	speed = IF_Gbps(10);
	
	if (link != 0 && sc->vmx_link_active == 0) {
		sc->vmx_link_active = 1;
		iflib_link_state_change(ctx, LINK_STATE_UP, speed);
	} else if (link == 0 && sc->vmx_link_active != 0) {
		sc->vmx_link_active = 0;
		iflib_link_state_change(ctx, LINK_STATE_DOWN, speed);
	}
}