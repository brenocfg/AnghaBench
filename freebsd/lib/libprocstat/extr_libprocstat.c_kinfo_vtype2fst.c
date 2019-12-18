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
#define  KF_VTYPE_VBAD 145 
#define  KF_VTYPE_VBLK 144 
#define  KF_VTYPE_VCHR 143 
#define  KF_VTYPE_VDIR 142 
#define  KF_VTYPE_VFIFO 141 
#define  KF_VTYPE_VLNK 140 
#define  KF_VTYPE_VNON 139 
#define  KF_VTYPE_VREG 138 
#define  KF_VTYPE_VSOCK 137 
 unsigned int NKFVTYPES ; 
 int PS_FST_VTYPE_UNKNOWN ; 
#define  PS_FST_VTYPE_VBAD 136 
#define  PS_FST_VTYPE_VBLK 135 
#define  PS_FST_VTYPE_VCHR 134 
#define  PS_FST_VTYPE_VDIR 133 
#define  PS_FST_VTYPE_VFIFO 132 
#define  PS_FST_VTYPE_VLNK 131 
#define  PS_FST_VTYPE_VNON 130 
#define  PS_FST_VTYPE_VREG 129 
#define  PS_FST_VTYPE_VSOCK 128 

__attribute__((used)) static int
kinfo_vtype2fst(int kfvtype)
{
	static struct {
		int	kf_vtype; 
		int	fst_vtype;
	} kfvtypes2fst[] = {
		{ KF_VTYPE_VBAD, PS_FST_VTYPE_VBAD },
		{ KF_VTYPE_VBLK, PS_FST_VTYPE_VBLK },
		{ KF_VTYPE_VCHR, PS_FST_VTYPE_VCHR },
		{ KF_VTYPE_VDIR, PS_FST_VTYPE_VDIR },
		{ KF_VTYPE_VFIFO, PS_FST_VTYPE_VFIFO },
		{ KF_VTYPE_VLNK, PS_FST_VTYPE_VLNK },
		{ KF_VTYPE_VNON, PS_FST_VTYPE_VNON },
		{ KF_VTYPE_VREG, PS_FST_VTYPE_VREG },
		{ KF_VTYPE_VSOCK, PS_FST_VTYPE_VSOCK }
	};
#define	NKFVTYPES	(sizeof(kfvtypes2fst) / sizeof(*kfvtypes2fst))
	unsigned int i;

	for (i = 0; i < NKFVTYPES; i++)
		if (kfvtypes2fst[i].kf_vtype == kfvtype)
			break;
	if (i == NKFVTYPES)
		return (PS_FST_VTYPE_UNKNOWN);
	return (kfvtypes2fst[i].fst_vtype);
}