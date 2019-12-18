#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct vesa_mode {int v_modeattr; int v_width; int v_height; int v_bpp; int v_planes; int v_cwidth; int v_cheight; int v_ipages; int v_memmodel; int v_lfb; int v_offscreen; int v_offscreensize; int v_waseg; int v_waattr; int v_wbseg; int v_wbattr; int v_wsize; int v_wgran; } ;
struct TYPE_2__ {int v_version; int v_memsize; int v_flags; int v_modetable; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int M_VESA_BASE ; 
 int M_VESA_MODE_MAX ; 
 int V_MODEGRAPHICS ; 
 int V_MODELFB ; 
 int V_MODEOPTINFO ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* vesa_adp_info ; 
 scalar_t__ vesa_bios_get_mode (int,struct vesa_mode*,int /*<<< orphan*/ ) ; 
 char* vesa_oemstr ; 
 char* vesa_prodstr ; 
 char* vesa_revstr ; 
 char* vesa_venderstr ; 
 int* vesa_vmodetab ; 

__attribute__((used)) static int
vesa_bios_info(int level)
{
#if VESA_DEBUG > 1
	struct vesa_mode vmode;
	int i;
#endif
	uint16_t vers;

	vers = vesa_adp_info->v_version;

	if (bootverbose) {
		/* general adapter information */
		printf(
	"VESA: v%d.%d, %dk memory, flags:0x%x, mode table:%p (%x)\n", 
		    (vers >> 12) * 10 + ((vers & 0x0f00) >> 8),
		    ((vers & 0x00f0) >> 4) * 10 + (vers & 0x000f),
		    vesa_adp_info->v_memsize * 64, vesa_adp_info->v_flags,
		    vesa_vmodetab, vesa_adp_info->v_modetable);

		/* OEM string */
		if (vesa_oemstr != NULL)
			printf("VESA: %s\n", vesa_oemstr);
	}

	if (level <= 0)
		return (0);

	if (vers >= 0x0200 && bootverbose) {
		/* vender name, product name, product revision */
		printf("VESA: %s %s %s\n",
			(vesa_venderstr != NULL) ? vesa_venderstr : "unknown",
			(vesa_prodstr != NULL) ? vesa_prodstr : "unknown",
			(vesa_revstr != NULL) ? vesa_revstr : "?");
	}

#if VESA_DEBUG > 1
	/* mode information */
	for (i = 0;
		(i < (M_VESA_MODE_MAX - M_VESA_BASE + 1))
		&& (vesa_vmodetab[i] != 0xffff); ++i) {
		if (vesa_bios_get_mode(vesa_vmodetab[i], &vmode, M_NOWAIT))
			continue;

		/* print something for diagnostic purpose */
		printf("VESA: mode:0x%03x, flags:0x%04x", 
		       vesa_vmodetab[i], vmode.v_modeattr);
		if (vmode.v_modeattr & V_MODEOPTINFO) {
			if (vmode.v_modeattr & V_MODEGRAPHICS) {
				printf(", G %dx%dx%d %d, ", 
				       vmode.v_width, vmode.v_height,
				       vmode.v_bpp, vmode.v_planes);
			} else {
				printf(", T %dx%d, ", 
				       vmode.v_width, vmode.v_height);
			}
			printf("font:%dx%d, ", 
			       vmode.v_cwidth, vmode.v_cheight);
			printf("pages:%d, mem:%d",
			       vmode.v_ipages + 1, vmode.v_memmodel);
		}
		if (vmode.v_modeattr & V_MODELFB) {
			printf("\nVESA: LFB:0x%x, off:0x%x, off_size:0x%x", 
			       vmode.v_lfb, vmode.v_offscreen,
			       vmode.v_offscreensize*1024);
		}
		printf("\n");
		printf("VESA: window A:0x%x (%x), window B:0x%x (%x), ",
		       vmode.v_waseg, vmode.v_waattr,
		       vmode.v_wbseg, vmode.v_wbattr);
		printf("size:%dk, gran:%dk\n",
		       vmode.v_wsize, vmode.v_wgran);
	}
#endif /* VESA_DEBUG > 1 */

	return (0);
}