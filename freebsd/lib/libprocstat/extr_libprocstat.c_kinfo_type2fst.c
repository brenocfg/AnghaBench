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
#define  KF_TYPE_CRYPTO 155 
#define  KF_TYPE_DEV 154 
#define  KF_TYPE_FIFO 153 
#define  KF_TYPE_KQUEUE 152 
#define  KF_TYPE_MQUEUE 151 
#define  KF_TYPE_NONE 150 
#define  KF_TYPE_PIPE 149 
#define  KF_TYPE_PROCDESC 148 
#define  KF_TYPE_PTS 147 
#define  KF_TYPE_SEM 146 
#define  KF_TYPE_SHM 145 
#define  KF_TYPE_SOCKET 144 
#define  KF_TYPE_UNKNOWN 143 
#define  KF_TYPE_VNODE 142 
 unsigned int NKFTYPES ; 
#define  PS_FST_TYPE_CRYPTO 141 
#define  PS_FST_TYPE_DEV 140 
#define  PS_FST_TYPE_FIFO 139 
#define  PS_FST_TYPE_KQUEUE 138 
#define  PS_FST_TYPE_MQUEUE 137 
#define  PS_FST_TYPE_NONE 136 
#define  PS_FST_TYPE_PIPE 135 
#define  PS_FST_TYPE_PROCDESC 134 
#define  PS_FST_TYPE_PTS 133 
#define  PS_FST_TYPE_SEM 132 
#define  PS_FST_TYPE_SHM 131 
#define  PS_FST_TYPE_SOCKET 130 
#define  PS_FST_TYPE_UNKNOWN 129 
#define  PS_FST_TYPE_VNODE 128 

__attribute__((used)) static int
kinfo_type2fst(int kftype)
{
	static struct {
		int	kf_type;
		int	fst_type;
	} kftypes2fst[] = {
		{ KF_TYPE_PROCDESC, PS_FST_TYPE_PROCDESC },
		{ KF_TYPE_CRYPTO, PS_FST_TYPE_CRYPTO },
		{ KF_TYPE_DEV, PS_FST_TYPE_DEV },
		{ KF_TYPE_FIFO, PS_FST_TYPE_FIFO },
		{ KF_TYPE_KQUEUE, PS_FST_TYPE_KQUEUE },
		{ KF_TYPE_MQUEUE, PS_FST_TYPE_MQUEUE },
		{ KF_TYPE_NONE, PS_FST_TYPE_NONE },
		{ KF_TYPE_PIPE, PS_FST_TYPE_PIPE },
		{ KF_TYPE_PTS, PS_FST_TYPE_PTS },
		{ KF_TYPE_SEM, PS_FST_TYPE_SEM },
		{ KF_TYPE_SHM, PS_FST_TYPE_SHM },
		{ KF_TYPE_SOCKET, PS_FST_TYPE_SOCKET },
		{ KF_TYPE_VNODE, PS_FST_TYPE_VNODE },
		{ KF_TYPE_UNKNOWN, PS_FST_TYPE_UNKNOWN }
	};
#define NKFTYPES	(sizeof(kftypes2fst) / sizeof(*kftypes2fst))
	unsigned int i;

	for (i = 0; i < NKFTYPES; i++)
		if (kftypes2fst[i].kf_type == kftype)
			break;
	if (i == NKFTYPES)
		return (PS_FST_TYPE_UNKNOWN);
	return (kftypes2fst[i].fst_type);
}