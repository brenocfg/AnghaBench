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
typedef  int uint32_t ;
struct terasic_mtl_softc {int dummy; } ;

/* Variables and functions */
 int TERASIC_MTL_BLEND_TEXTFG_MASK ; 
 int TERASIC_MTL_BLEND_TEXTFG_SHIFT ; 
 int /*<<< orphan*/  TERASIC_MTL_LOCK (struct terasic_mtl_softc*) ; 
 int /*<<< orphan*/  TERASIC_MTL_UNLOCK (struct terasic_mtl_softc*) ; 
 int /*<<< orphan*/  terasic_mtl_reg_blend_get (struct terasic_mtl_softc*,int*) ; 
 int /*<<< orphan*/  terasic_mtl_reg_blend_set (struct terasic_mtl_softc*,int) ; 

void
terasic_mtl_blend_textfg_set(struct terasic_mtl_softc *sc, uint8_t alpha)
{
	uint32_t v;

	TERASIC_MTL_LOCK(sc);
	terasic_mtl_reg_blend_get(sc, &v);
	v &= ~TERASIC_MTL_BLEND_TEXTFG_MASK;
	v |= alpha << TERASIC_MTL_BLEND_TEXTFG_SHIFT;
	terasic_mtl_reg_blend_set(sc, v);
	TERASIC_MTL_UNLOCK(sc);
}