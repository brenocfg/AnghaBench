#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ _ISO2022EncodingInfo ;

/* Variables and functions */
#define  F_8BIT 142 
#define  F_LS0 141 
#define  F_LS1 140 
#define  F_LS1R 139 
#define  F_LS2 138 
#define  F_LS2R 137 
#define  F_LS3 136 
#define  F_LS3R 135 
#define  F_NOOLD 134 
#define  F_SI 133 
#define  F_SO 132 
#define  F_SS2 131 
#define  F_SS2R 130 
#define  F_SS3 129 
#define  F_SS3R 128 
 int _MATCH ; 
 int _NOTMATCH ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static __inline int
get_flags(_ISO2022EncodingInfo * __restrict ei,
    const char * __restrict token)
{
	static struct {
		const char	*tag;
		int		flag;
	} const tags[] = {
		{ "DUMMY",	0	},
		{ "8BIT",	F_8BIT	},
		{ "NOOLD",	F_NOOLD	},
		{ "SI",		F_SI	},
		{ "SO",		F_SO	},
		{ "LS0",	F_LS0	},
		{ "LS1",	F_LS1	},
		{ "LS2",	F_LS2	},
		{ "LS3",	F_LS3	},
		{ "LS1R",	F_LS1R	},
		{ "LS2R",	F_LS2R	},
		{ "LS3R",	F_LS3R	},
		{ "SS2",	F_SS2	},
		{ "SS3",	F_SS3	},
		{ "SS2R",	F_SS2R	},
		{ "SS3R",	F_SS3R	},
		{ NULL,		0 }
	};
	int i;

	for (i = 0; tags[i].tag; i++)
		if (!strcmp(token, tags[i].tag)) {
			ei->flags |= tags[i].flag;
			return (_MATCH);
		}

	return (_NOTMATCH);
}