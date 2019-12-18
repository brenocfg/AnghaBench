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
typedef  int uint8_t ;
struct ecore_credit_pool_obj {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int ECORE_CAM_SIZE_EMUL ; 
 int ECORE_MAX_EMUL_MULTI ; 
 int ECORE_MAX_MULTICAST ; 
 int MAX_MAC_CREDIT_E1 ; 
 int MAX_MAC_CREDIT_E1H ; 
 int PF_MAC_CREDIT_E2 (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  ecore_init_credit_pool (struct ecore_credit_pool_obj*,int,int) ; 

void ecore_init_mac_credit_pool(struct bxe_softc *sc,
				struct ecore_credit_pool_obj *p, uint8_t func_id,
				uint8_t func_num)
{
/* TODO: this will be defined in consts as well... */
#define ECORE_CAM_SIZE_EMUL 5

	int cam_sz;

	if (CHIP_IS_E1(sc)) {
		/* In E1, Multicast is saved in cam... */
		if (!CHIP_REV_IS_SLOW(sc))
			cam_sz = (MAX_MAC_CREDIT_E1 / 2) - ECORE_MAX_MULTICAST;
		else
			cam_sz = ECORE_CAM_SIZE_EMUL - ECORE_MAX_EMUL_MULTI;

		ecore_init_credit_pool(p, func_id * cam_sz, cam_sz);

	} else if (CHIP_IS_E1H(sc)) {
		/* CAM credit is equally divided between all active functions
		 * on the PORT!.
		 */
		if ((func_num > 0)) {
			if (!CHIP_REV_IS_SLOW(sc))
				cam_sz = (MAX_MAC_CREDIT_E1H / (2*func_num));
			else
				cam_sz = ECORE_CAM_SIZE_EMUL;
			ecore_init_credit_pool(p, func_id * cam_sz, cam_sz);
		} else {
			/* this should never happen! Block MAC operations. */
			ecore_init_credit_pool(p, 0, 0);
		}
	} else {
		/*
		 * CAM credit is equaly divided between all active functions
		 * on the PATH.
		 */
		if (func_num > 0) {
			if (!CHIP_REV_IS_SLOW(sc))
				cam_sz = PF_MAC_CREDIT_E2(sc, func_num);
			else
				cam_sz = ECORE_CAM_SIZE_EMUL;

			/* No need for CAM entries handling for 57712 and
			 * newer.
			 */
			ecore_init_credit_pool(p, -1, cam_sz);
		} else {
			/* this should never happen! Block MAC operations. */
			ecore_init_credit_pool(p, 0, 0);
		}
	}
}