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
#define  KD_CGA 154 
#define  KD_EGA 153 
#define  KD_HERCULES 152 
#define  KD_MONO 151 
#define  KD_VGA 150 
#define  M_B40x25 149 
#define  M_B80x25 148 
#define  M_BG320 147 
#define  M_BG640 146 
#define  M_BG640x480 145 
#define  M_C40x25 144 
#define  M_C80x25 143 
#define  M_CG320 142 
#define  M_CG320_D 141 
#define  M_CG640_E 140 
#define  M_CG640x480 139 
#define  M_EGAMONO80x25 138 
#define  M_ENHMONOAPA2 137 
#define  M_ENH_B40x25 136 
#define  M_ENH_B80x25 135 
#define  M_ENH_C40x25 134 
#define  M_ENH_C80x25 133 
#define  M_ENH_CG640 132 
#define  M_VGA_C40x25 131 
#define  M_VGA_C80x25 130 
#define  M_VGA_CG320 129 
#define  M_VGA_M80x25 128 
 int nitems (int*) ; 

__attribute__((used)) static int
map_bios_mode_num(int type, int color, int bios_mode)
{
    static int cga_modes[7] = {
	M_B40x25, M_C40x25,		/* 0, 1 */
	M_B80x25, M_C80x25,		/* 2, 3 */
	M_BG320, M_CG320,
	M_BG640,
    };
    static int ega_modes[17] = {
	M_ENH_B40x25, M_ENH_C40x25,	/* 0, 1 */
	M_ENH_B80x25, M_ENH_C80x25,	/* 2, 3 */
	M_BG320, M_CG320,
	M_BG640,
	M_EGAMONO80x25,			/* 7 */
	8, 9, 10, 11, 12,
	M_CG320_D,
	M_CG640_E,
	M_ENHMONOAPA2,			/* XXX: video momery > 64K */
	M_ENH_CG640,			/* XXX: video momery > 64K */
    };
    static int vga_modes[20] = {
	M_VGA_C40x25, M_VGA_C40x25,	/* 0, 1 */
	M_VGA_C80x25, M_VGA_C80x25,	/* 2, 3 */
	M_BG320, M_CG320,
	M_BG640,
	M_VGA_M80x25,			/* 7 */
	8, 9, 10, 11, 12,
	M_CG320_D,
	M_CG640_E,
	M_ENHMONOAPA2,
	M_ENH_CG640,
	M_BG640x480, M_CG640x480, 
	M_VGA_CG320,
    };

    switch (type) {

    case KD_VGA:
	if (bios_mode < nitems(vga_modes))
	    return vga_modes[bios_mode];
	else if (color)
	    return M_VGA_C80x25;
	else
	    return M_VGA_M80x25;
	break;

    case KD_EGA:
	if (bios_mode < nitems(ega_modes))
	    return ega_modes[bios_mode];
	else if (color)
	    return M_ENH_C80x25;
	else
	    return M_EGAMONO80x25;
	break;

    case KD_CGA:
	if (bios_mode < nitems(cga_modes))
	    return cga_modes[bios_mode];
	else
	    return M_C80x25;
	break;

    case KD_MONO:
    case KD_HERCULES:
	return M_EGAMONO80x25;		/* XXX: this name is confusing */

    default:
	break;
    }
    return -1;
}