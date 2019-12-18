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
typedef  int uint32_t ;
struct hda_softc {int dummy; } ;

/* Variables and functions */
 int hda_get_reg_by_offset (struct hda_softc*,int) ; 
 int /*<<< orphan*/  hda_set_reg_by_offset (struct hda_softc*,int,int) ; 

__attribute__((used)) static inline void
hda_set_field_by_offset(struct hda_softc *sc, uint32_t offset,
    uint32_t mask, uint32_t value)
{
	uint32_t reg_value = 0;

	reg_value = hda_get_reg_by_offset(sc, offset);

	reg_value &= ~mask;
	reg_value |= (value & mask);

	hda_set_reg_by_offset(sc, offset, reg_value);
}