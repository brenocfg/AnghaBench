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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bwi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_DBG_ATTACH ; 
 int /*<<< orphan*/  BWI_ID_HI ; 
 int /*<<< orphan*/  BWI_ID_HI_REGWIN_REV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWI_ID_HI_REGWIN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWI_ID_HI_REGWIN_VENDOR_MASK ; 
 int /*<<< orphan*/  CSR_READ_4 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (struct bwi_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __SHIFTOUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_regwin_info(struct bwi_softc *sc, uint16_t *type, uint8_t *rev)
{
	uint32_t val;

	val = CSR_READ_4(sc, BWI_ID_HI);
	*type = BWI_ID_HI_REGWIN_TYPE(val);
	*rev = BWI_ID_HI_REGWIN_REV(val);

	DPRINTF(sc, BWI_DBG_ATTACH, "regwin: type 0x%03x, rev %d, "
		"vendor 0x%04x\n", *type, *rev,
		__SHIFTOUT(val, BWI_ID_HI_REGWIN_VENDOR_MASK));
}