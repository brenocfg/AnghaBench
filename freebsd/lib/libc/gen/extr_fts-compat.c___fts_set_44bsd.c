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
struct TYPE_3__ {int fts_instr; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int FTS_AGAIN ; 
 int FTS_FOLLOW ; 
 int FTS_NOINSTR ; 
 int FTS_SKIP ; 
 int /*<<< orphan*/  errno ; 

int
__fts_set_44bsd(FTS *sp, FTSENT *p, int instr)
{
	if (instr != 0 && instr != FTS_AGAIN && instr != FTS_FOLLOW &&
	    instr != FTS_NOINSTR && instr != FTS_SKIP) {
		errno = EINVAL;
		return (1);
	}
	p->fts_instr = instr;
	return (0);
}