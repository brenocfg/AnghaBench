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
 unsigned int NVFTYPES ; 
 unsigned int PS_FST_VTYPE_UNKNOWN ; 
#define  PS_FST_VTYPE_VBAD 145 
#define  PS_FST_VTYPE_VBLK 144 
#define  PS_FST_VTYPE_VCHR 143 
#define  PS_FST_VTYPE_VDIR 142 
#define  PS_FST_VTYPE_VFIFO 141 
#define  PS_FST_VTYPE_VLNK 140 
#define  PS_FST_VTYPE_VNON 139 
#define  PS_FST_VTYPE_VREG 138 
#define  PS_FST_VTYPE_VSOCK 137 
#define  VBAD 136 
#define  VBLK 135 
#define  VCHR 134 
#define  VDIR 133 
#define  VFIFO 132 
#define  VLNK 131 
#define  VNON 130 
#define  VREG 129 
#define  VSOCK 128 

__attribute__((used)) static int
vntype2psfsttype(int type)
{
	static struct {
		int	vtype; 
		int	fst_vtype;
	} vt2fst[] = {
		{ VBAD, PS_FST_VTYPE_VBAD },
		{ VBLK, PS_FST_VTYPE_VBLK },
		{ VCHR, PS_FST_VTYPE_VCHR },
		{ VDIR, PS_FST_VTYPE_VDIR },
		{ VFIFO, PS_FST_VTYPE_VFIFO },
		{ VLNK, PS_FST_VTYPE_VLNK },
		{ VNON, PS_FST_VTYPE_VNON },
		{ VREG, PS_FST_VTYPE_VREG },
		{ VSOCK, PS_FST_VTYPE_VSOCK }
	};
#define	NVFTYPES	(sizeof(vt2fst) / sizeof(*vt2fst))
	unsigned int i, fst_type;

	fst_type = PS_FST_VTYPE_UNKNOWN;
	for (i = 0; i < NVFTYPES; i++) {
		if (type == vt2fst[i].vtype) {
			fst_type = vt2fst[i].fst_vtype;
			break;
		}
	}
	return (fst_type);
}