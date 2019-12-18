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
#define  FREAD 155 
#define  FWRITE 154 
 unsigned int NFSTFLAGS ; 
#define  O_APPEND 153 
#define  O_ASYNC 152 
#define  O_CREAT 151 
#define  O_DIRECT 150 
#define  O_EXCL 149 
#define  O_EXEC 148 
#define  O_EXLOCK 147 
#define  O_NOFOLLOW 146 
#define  O_NONBLOCK 145 
#define  O_SHLOCK 144 
#define  O_SYNC 143 
#define  O_TRUNC 142 
#define  PS_FST_FFLAG_APPEND 141 
#define  PS_FST_FFLAG_ASYNC 140 
#define  PS_FST_FFLAG_CREAT 139 
#define  PS_FST_FFLAG_DIRECT 138 
#define  PS_FST_FFLAG_EXCL 137 
#define  PS_FST_FFLAG_EXEC 136 
#define  PS_FST_FFLAG_EXLOCK 135 
#define  PS_FST_FFLAG_NOFOLLOW 134 
#define  PS_FST_FFLAG_NONBLOCK 133 
#define  PS_FST_FFLAG_READ 132 
#define  PS_FST_FFLAG_SHLOCK 131 
#define  PS_FST_FFLAG_SYNC 130 
#define  PS_FST_FFLAG_TRUNC 129 
#define  PS_FST_FFLAG_WRITE 128 

__attribute__((used)) static int
to_filestat_flags(int flags)
{
	static struct {
		int flag;
		int fst_flag;
	} fstflags[] = {
		{ FREAD, PS_FST_FFLAG_READ },
		{ FWRITE, PS_FST_FFLAG_WRITE },
		{ O_APPEND, PS_FST_FFLAG_APPEND },
		{ O_ASYNC, PS_FST_FFLAG_ASYNC },
		{ O_CREAT, PS_FST_FFLAG_CREAT },
		{ O_DIRECT, PS_FST_FFLAG_DIRECT },
		{ O_EXCL, PS_FST_FFLAG_EXCL },
		{ O_EXEC, PS_FST_FFLAG_EXEC },
		{ O_EXLOCK, PS_FST_FFLAG_EXLOCK },
		{ O_NOFOLLOW, PS_FST_FFLAG_NOFOLLOW },
		{ O_NONBLOCK, PS_FST_FFLAG_NONBLOCK },
		{ O_SHLOCK, PS_FST_FFLAG_SHLOCK },
		{ O_SYNC, PS_FST_FFLAG_SYNC },
		{ O_TRUNC, PS_FST_FFLAG_TRUNC }
	};
#define NFSTFLAGS	(sizeof(fstflags) / sizeof(*fstflags))
	int fst_flags;
	unsigned int i;

	fst_flags = 0;
	for (i = 0; i < NFSTFLAGS; i++)
		if (flags & fstflags[i].flag)
			fst_flags |= fstflags[i].fst_flag;
	return (fst_flags);
}