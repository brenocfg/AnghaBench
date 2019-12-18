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
typedef  int /*<<< orphan*/  uint32_t ;
struct terasic_mtl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERASIC_MTL_BLEND_PIXEL_ENDIAN_SWAP ; 
 int /*<<< orphan*/  TERASIC_MTL_LOCK (struct terasic_mtl_softc*) ; 
 int /*<<< orphan*/  TERASIC_MTL_UNLOCK (struct terasic_mtl_softc*) ; 
 int /*<<< orphan*/  terasic_mtl_reg_blend_get (struct terasic_mtl_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terasic_mtl_reg_blend_set (struct terasic_mtl_softc*,int /*<<< orphan*/ ) ; 

void
terasic_mtl_reg_pixel_endian_set(struct terasic_mtl_softc *sc, int endian_swap)
{
	uint32_t v;

	TERASIC_MTL_LOCK(sc);
	terasic_mtl_reg_blend_get(sc, &v);
	if (endian_swap)
		v |= TERASIC_MTL_BLEND_PIXEL_ENDIAN_SWAP;
	else
		v &= ~TERASIC_MTL_BLEND_PIXEL_ENDIAN_SWAP;
	terasic_mtl_reg_blend_set(sc, v);
	TERASIC_MTL_UNLOCK(sc);
}