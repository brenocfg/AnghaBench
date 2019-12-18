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
typedef  size_t uint32_t ;
struct hda_softc {size_t* regs; } ;

/* Variables and functions */
 size_t HDA_LAST_OFFSET ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline uint32_t
hda_get_reg_by_offset(struct hda_softc *sc, uint32_t offset)
{
	assert(offset < HDA_LAST_OFFSET);
	return sc->regs[offset];
}