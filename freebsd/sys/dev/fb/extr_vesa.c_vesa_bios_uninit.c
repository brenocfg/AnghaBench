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

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  VESA_BIOS_OFFSET ; 
 scalar_t__ VESA_PALETTE_SIZE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vesa_adp_info ; 
 int /*<<< orphan*/ * vesa_bios ; 
 int /*<<< orphan*/  vesa_bios_int10 ; 
 int /*<<< orphan*/  vesa_bios_offs ; 
 scalar_t__ vesa_bios_size ; 
 int /*<<< orphan*/ * vesa_oemstr ; 
 int /*<<< orphan*/ * vesa_palette ; 
 int /*<<< orphan*/ * vesa_prodstr ; 
 int /*<<< orphan*/ * vesa_revstr ; 
 scalar_t__ vesa_state_buf_size ; 
 int /*<<< orphan*/ * vesa_venderstr ; 
 int /*<<< orphan*/ * vesa_vmode ; 
 int /*<<< orphan*/  x86bios_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  x86bios_set_intr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vesa_bios_uninit(void)
{

	if (vesa_bios != NULL) {
		x86bios_set_intr(0x10, vesa_bios_int10);
		vesa_bios_offs = VESA_BIOS_OFFSET;
		x86bios_free(vesa_bios, vesa_bios_size);
		vesa_bios = NULL;
	}
	if (vesa_adp_info != NULL) {
		free(vesa_adp_info, M_DEVBUF);
		vesa_adp_info = NULL;
	}
	if (vesa_oemstr != NULL) {
		free(vesa_oemstr, M_DEVBUF);
		vesa_oemstr = NULL;
	}
	if (vesa_venderstr != NULL) {
		free(vesa_venderstr, M_DEVBUF);
		vesa_venderstr = NULL;
	}
	if (vesa_prodstr != NULL) {
		free(vesa_prodstr, M_DEVBUF);
		vesa_prodstr = NULL;
	}
	if (vesa_revstr != NULL) {
		free(vesa_revstr, M_DEVBUF);
		vesa_revstr = NULL;
	}
	if (vesa_vmode != NULL) {
		free(vesa_vmode, M_DEVBUF);
		vesa_vmode = NULL;
	}
	if (vesa_palette != NULL) {
		x86bios_free(vesa_palette,
		    VESA_PALETTE_SIZE + vesa_state_buf_size);
		vesa_palette = NULL;
	}
}