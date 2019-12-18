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
#define  KF_FLAG_APPEND 157 
#define  KF_FLAG_ASYNC 156 
#define  KF_FLAG_CREAT 155 
#define  KF_FLAG_DIRECT 154 
#define  KF_FLAG_EXCL 153 
#define  KF_FLAG_EXEC 152 
#define  KF_FLAG_EXLOCK 151 
#define  KF_FLAG_FSYNC 150 
#define  KF_FLAG_HASLOCK 149 
#define  KF_FLAG_NOFOLLOW 148 
#define  KF_FLAG_NONBLOCK 147 
#define  KF_FLAG_READ 146 
#define  KF_FLAG_SHLOCK 145 
#define  KF_FLAG_TRUNC 144 
#define  KF_FLAG_WRITE 143 
 unsigned int NKFFLAGS ; 
#define  PS_FST_FFLAG_APPEND 142 
#define  PS_FST_FFLAG_ASYNC 141 
#define  PS_FST_FFLAG_CREAT 140 
#define  PS_FST_FFLAG_DIRECT 139 
#define  PS_FST_FFLAG_EXCL 138 
#define  PS_FST_FFLAG_EXEC 137 
#define  PS_FST_FFLAG_EXLOCK 136 
#define  PS_FST_FFLAG_HASLOCK 135 
#define  PS_FST_FFLAG_NOFOLLOW 134 
#define  PS_FST_FFLAG_NONBLOCK 133 
#define  PS_FST_FFLAG_READ 132 
#define  PS_FST_FFLAG_SHLOCK 131 
#define  PS_FST_FFLAG_SYNC 130 
#define  PS_FST_FFLAG_TRUNC 129 
#define  PS_FST_FFLAG_WRITE 128 

__attribute__((used)) static int
kinfo_fflags2fst(int kfflags)
{
	static struct {
		int	kf_flag;
		int	fst_flag;
	} kfflags2fst[] = {
		{ KF_FLAG_APPEND, PS_FST_FFLAG_APPEND },
		{ KF_FLAG_ASYNC, PS_FST_FFLAG_ASYNC },
		{ KF_FLAG_CREAT, PS_FST_FFLAG_CREAT },
		{ KF_FLAG_DIRECT, PS_FST_FFLAG_DIRECT },
		{ KF_FLAG_EXCL, PS_FST_FFLAG_EXCL },
		{ KF_FLAG_EXEC, PS_FST_FFLAG_EXEC },
		{ KF_FLAG_EXLOCK, PS_FST_FFLAG_EXLOCK },
		{ KF_FLAG_FSYNC, PS_FST_FFLAG_SYNC },
		{ KF_FLAG_HASLOCK, PS_FST_FFLAG_HASLOCK },
		{ KF_FLAG_NOFOLLOW, PS_FST_FFLAG_NOFOLLOW },
		{ KF_FLAG_NONBLOCK, PS_FST_FFLAG_NONBLOCK },
		{ KF_FLAG_READ, PS_FST_FFLAG_READ },
		{ KF_FLAG_SHLOCK, PS_FST_FFLAG_SHLOCK },
		{ KF_FLAG_TRUNC, PS_FST_FFLAG_TRUNC },
		{ KF_FLAG_WRITE, PS_FST_FFLAG_WRITE }
	};
#define NKFFLAGS	(sizeof(kfflags2fst) / sizeof(*kfflags2fst))
	unsigned int i;
	int flags;

	flags = 0;
	for (i = 0; i < NKFFLAGS; i++)
		if ((kfflags & kfflags2fst[i].kf_flag) != 0)
			flags |= kfflags2fst[i].fst_flag;
	return (flags);
}