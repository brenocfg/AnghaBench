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
struct ptrace_lwpinfo {unsigned int pl_flags; } ;
typedef  int /*<<< orphan*/  flags ;
typedef  int /*<<< orphan*/  decode ;
typedef  int /*<<< orphan*/  de ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int NBBY ; 
#define  PL_FLAG_BORN 139 
#define  PL_FLAG_BOUND 138 
#define  PL_FLAG_CHILD 137 
#define  PL_FLAG_EXEC 136 
#define  PL_FLAG_EXITED 135 
#define  PL_FLAG_FORKED 134 
#define  PL_FLAG_SA 133 
#define  PL_FLAG_SCE 132 
#define  PL_FLAG_SCX 131 
#define  PL_FLAG_SI 130 
#define  PL_FLAG_VFORKED 129 
#define  PL_FLAG_VFORK_DONE 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

__attribute__((used)) static const char *
decode_pl_flags(struct ptrace_lwpinfo *lwpinfo)
{
	static char c[128];
	static struct decode_tag {
		int flag;
		const char *desc;
	} decode[] = {
		{ PL_FLAG_SA, "SA" },
		{ PL_FLAG_BOUND, "BOUND" },
		{ PL_FLAG_SCE, "SCE" },
		{ PL_FLAG_SCX, "SCX" },
		{ PL_FLAG_EXEC, "EXEC" },
		{ PL_FLAG_SI, "SI" },
		{ PL_FLAG_FORKED, "FORKED" },
		{ PL_FLAG_CHILD, "CHILD" },
		{ PL_FLAG_BORN, "LWPBORN" },
		{ PL_FLAG_EXITED, "LWPEXITED" },
		{ PL_FLAG_VFORKED, "VFORKED" },
		{ PL_FLAG_VFORK_DONE, "VFORKDONE" },
	};
	char de[32];
	unsigned first, flags, i;

	c[0] = '\0';
	first = 1;
	flags = lwpinfo->pl_flags;
	for (i = 0; i < sizeof(decode) / sizeof(decode[0]); i++) {
		if ((flags & decode[i].flag) != 0) {
			if (first)
				first = 0;
			else
				strlcat(c, ",", sizeof(c));
			strlcat(c, decode[i].desc, sizeof(c));
			flags &= ~decode[i].flag;
		}
	}
	for (i = 0; i < sizeof(flags) * NBBY; i++) {
		if ((flags & (1 << i)) != 0) {
			if (first)
				first = 0;
			else
				strlcat(c, ",", sizeof(c));
			snprintf(de, sizeof(de), "<%d>", i);
			strlcat(c, de, sizeof(c));
		}
	}
	return (c);
}