#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  vi_flags; } ;
typedef  TYPE_1__ video_info_t ;
struct TYPE_15__ {int va_flags; int va_mode; int /*<<< orphan*/  va_type; } ;
typedef  TYPE_2__ video_adapter_t ;
struct TYPE_16__ {int* regs; int /*<<< orphan*/  sig; } ;
typedef  TYPE_3__ adp_state_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  M_B40x25 168 
#define  M_B80x25 167 
#define  M_BG320 166 
#define  M_BG640 165 
#define  M_BG640x480 164 
#define  M_C40x25 163 
#define  M_C80x25 162 
#define  M_CG320 161 
#define  M_CG320_D 160 
#define  M_CG640_E 159 
#define  M_CG640x350 158 
#define  M_CG640x480 157 
#define  M_EGAMONO80x25 156 
#define  M_ENH_B40x25 155 
#define  M_ENH_B80x25 154 
#define  M_ENH_B80x43 153 
#define  M_ENH_C40x25 152 
#define  M_ENH_C80x25 151 
#define  M_ENH_C80x43 150 
#define  M_ENH_CG640 149 
#define  M_VGA_C40x25 148 
#define  M_VGA_C80x25 147 
#define  M_VGA_C80x30 146 
#define  M_VGA_C80x50 145 
#define  M_VGA_C80x60 144 
#define  M_VGA_C90x25 143 
#define  M_VGA_C90x30 142 
#define  M_VGA_C90x43 141 
#define  M_VGA_C90x50 140 
#define  M_VGA_C90x60 139 
#define  M_VGA_CG320 138 
#define  M_VGA_M80x25 137 
#define  M_VGA_M80x30 136 
#define  M_VGA_M80x50 135 
#define  M_VGA_M80x60 134 
#define  M_VGA_M90x25 133 
#define  M_VGA_M90x30 132 
#define  M_VGA_M90x43 131 
#define  M_VGA_M90x50 130 
#define  M_VGA_M90x60 129 
#define  M_VGA_MODEX 128 
 int V_ADP_COLOR ; 
 int /*<<< orphan*/  V_ADP_MODECHANGE ; 
 int /*<<< orphan*/  V_INFO_LINEAR ; 
 int /*<<< orphan*/  V_STATE_SIG ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  get_mode_param (int) ; 
 int map_gen_mode_num (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  prologue (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_width90 (TYPE_3__*) ; 
 int /*<<< orphan*/  update_adapter_info (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ vga_get_info (TYPE_2__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  vga_load_state (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  vidd_set_hw_cursor (TYPE_2__*,int,int) ; 

__attribute__((used)) static int
vga_set_mode(video_adapter_t *adp, int mode)
{
#ifndef VGA_NO_MODE_CHANGE
    video_info_t info;
    adp_state_t params;

    prologue(adp, V_ADP_MODECHANGE, ENODEV);

    mode = map_gen_mode_num(adp->va_type, 
			    adp->va_flags & V_ADP_COLOR, mode);
    if (vga_get_info(adp, mode, &info))
	return EINVAL;

#if VGA_DEBUG > 1
    printf("vga_set_mode(): setting mode %d\n", mode);
#endif

    params.sig = V_STATE_SIG;
    bcopy(get_mode_param(mode), params.regs, sizeof(params.regs));

    switch (mode) {
#ifdef VGA_WIDTH90
    case M_VGA_C90x60: case M_VGA_M90x60:
	set_width90(&params);
	/* FALLTHROUGH */
#endif
    case M_VGA_C80x60: case M_VGA_M80x60:
	params.regs[2]  = 0x08;
	params.regs[19] = 0x47;
	goto special_480l;

#ifdef VGA_WIDTH90
    case M_VGA_C90x30: case M_VGA_M90x30:
	set_width90(&params);
	/* FALLTHROUGH */
#endif
    case M_VGA_C80x30: case M_VGA_M80x30:
	params.regs[19] = 0x4f;
special_480l:
	params.regs[9] |= 0xc0;
	params.regs[16] = 0x08;
	params.regs[17] = 0x3e;
	params.regs[26] = 0xea;
	params.regs[28] = 0xdf;
	params.regs[31] = 0xe7;
	params.regs[32] = 0x04;
	goto setup_mode;

#ifdef VGA_WIDTH90
    case M_VGA_C90x43: case M_VGA_M90x43:
	set_width90(&params);
	/* FALLTHROUGH */
#endif
    case M_ENH_C80x43: case M_ENH_B80x43:
	params.regs[28] = 87;
	goto special_80x50;

#ifdef VGA_WIDTH90
    case M_VGA_C90x50: case M_VGA_M90x50:
	set_width90(&params);
	/* FALLTHROUGH */
#endif
    case M_VGA_C80x50: case M_VGA_M80x50:
special_80x50:
	params.regs[2] = 8;
	params.regs[19] = 7;
	goto setup_mode;

#ifdef VGA_WIDTH90
    case M_VGA_C90x25: case M_VGA_M90x25:
	set_width90(&params);
	/* FALLTHROUGH */
#endif
    case M_VGA_C40x25: case M_VGA_C80x25:
    case M_VGA_M80x25:
    case M_B40x25:     case M_C40x25:
    case M_B80x25:     case M_C80x25:
    case M_ENH_B40x25: case M_ENH_C40x25:
    case M_ENH_B80x25: case M_ENH_C80x25:
    case M_EGAMONO80x25:

setup_mode:
	vga_load_state(adp, &params);
	break;

    case M_VGA_MODEX:
	/* "unchain" the VGA mode */
	params.regs[5-1+0x04] &= 0xf7;
	params.regs[5-1+0x04] |= 0x04;
	/* turn off doubleword mode */
	params.regs[10+0x14] &= 0xbf;
	/* turn off word addressing */
	params.regs[10+0x17] |= 0x40;
	/* set logical screen width */
	params.regs[10+0x13] = 80;
	/* set 240 lines */
	params.regs[10+0x11] = 0x2c;
	params.regs[10+0x06] = 0x0d;
	params.regs[10+0x07] = 0x3e;
	params.regs[10+0x10] = 0xea;
	params.regs[10+0x11] = 0xac;
	params.regs[10+0x12] = 0xdf;
	params.regs[10+0x15] = 0xe7;
	params.regs[10+0x16] = 0x06;
	/* set vertical sync polarity to reflect aspect ratio */
	params.regs[9] = 0xe3;
	goto setup_grmode;

    case M_BG320:     case M_CG320:     case M_BG640:
    case M_CG320_D:   case M_CG640_E:
    case M_CG640x350: case M_ENH_CG640:
    case M_BG640x480: case M_CG640x480: case M_VGA_CG320:

setup_grmode:
	vga_load_state(adp, &params);
	break;

    default:
	return EINVAL;
    }

    adp->va_mode = mode;
    info.vi_flags &= ~V_INFO_LINEAR; /* XXX */
    update_adapter_info(adp, &info);

    /* move hardware cursor out of the way */
    vidd_set_hw_cursor(adp, -1, -1);

    return 0;
#else /* VGA_NO_MODE_CHANGE */
    return ENODEV;
#endif /* VGA_NO_MODE_CHANGE */
}