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
struct iwm_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwm_set_bits_mask_prph (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iwm_clear_bits_prph(struct iwm_softc *sc, uint32_t reg, uint32_t bits)
{
	iwm_set_bits_mask_prph(sc, reg, 0, ~bits);
}