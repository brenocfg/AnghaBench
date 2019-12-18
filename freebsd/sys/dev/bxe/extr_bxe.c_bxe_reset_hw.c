#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  load_phase; } ;
struct TYPE_4__ {TYPE_1__ hw_init; } ;
struct ecore_func_state_params {TYPE_2__ params; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * f_obj; int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/ * member_0; } ;
struct bxe_softc {int /*<<< orphan*/  func_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_F_CMD_HW_RESET ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_func_state_change (struct bxe_softc*,struct ecore_func_state_params*) ; 

__attribute__((used)) static int
bxe_reset_hw(struct bxe_softc *sc,
             uint32_t         load_code)
{
    struct ecore_func_state_params func_params = { NULL };

    /* Prepare parameters for function state transitions */
    bxe_set_bit(RAMROD_COMP_WAIT, &func_params.ramrod_flags);

    func_params.f_obj = &sc->func_obj;
    func_params.cmd = ECORE_F_CMD_HW_RESET;

    func_params.params.hw_init.load_phase = load_code;

    return (ecore_func_state_change(sc, &func_params));
}