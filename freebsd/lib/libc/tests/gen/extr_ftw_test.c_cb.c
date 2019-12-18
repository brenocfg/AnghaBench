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
struct stat {int dummy; } ;
struct FTW {int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_MSG (int,char*,char const*,int,int /*<<< orphan*/ ) ; 
#define  FTW_D 130 
 int FTW_DEPTH ; 
#define  FTW_DP 129 
 int FTW_PHYS ; 
#define  FTW_SL 128 
 int ftwflags ; 

__attribute__((used)) static int
cb(const char *path, const struct stat *st, int type, struct FTW *f)
{

	switch (type) {
	case FTW_D:
		if ((ftwflags & FTW_DEPTH) == 0)
			return (0);
		break;
	case FTW_DP:
		if ((ftwflags & FTW_DEPTH) != 0)
			return (0);
		break;
	case FTW_SL:
		if ((ftwflags & FTW_PHYS) != 0)
			return (0);
		break;
	}
	ATF_CHECK_MSG(false,
	    "unexpected path=%s type=%d f.level=%d\n",
	    path, type, f->level);
	return (0);
}