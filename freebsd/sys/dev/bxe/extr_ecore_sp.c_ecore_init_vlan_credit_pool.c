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
typedef  scalar_t__ uint8_t ;
struct ecore_credit_pool_obj {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 int PF_VLAN_CREDIT_E2 (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_init_credit_pool (struct ecore_credit_pool_obj*,int,int) ; 

void ecore_init_vlan_credit_pool(struct bxe_softc *sc,
				 struct ecore_credit_pool_obj *p,
				 uint8_t func_id,
				 uint8_t func_num)
{
	if (CHIP_IS_E1x(sc)) {
		/* There is no VLAN credit in HW on 57710 and 57711 only
		 * MAC / MAC-VLAN can be set
		 */
		ecore_init_credit_pool(p, 0, -1);
	} else {
		/* CAM credit is equally divided between all active functions
		 * on the PATH.
		 */
		if (func_num > 0) {
			int credit = PF_VLAN_CREDIT_E2(sc, func_num);

			ecore_init_credit_pool(p, -1/*unused for E2*/, credit);
		} else
			/* this should never happen! Block VLAN operations. */
			ecore_init_credit_pool(p, 0, 0);
	}
}