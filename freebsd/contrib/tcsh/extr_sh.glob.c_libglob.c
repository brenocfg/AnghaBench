#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ gl_pathc; int gl_flags; scalar_t__ gl_matchc; scalar_t__ gl_pathv; scalar_t__ gl_offs; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_GLOB ; 
 int ERR_NAME ; 
 int ERR_NOMEM ; 
#define  GLOB_ABEND 129 
 int GLOB_ALTNOT ; 
 int GLOB_APPEND ; 
 int GLOB_DOT ; 
 int GLOB_MAGCHAR ; 
 int GLOB_NOCHECK ; 
 int GLOB_NOMAGIC ; 
#define  GLOB_NOSPACE 128 
 int GLOB_QUOTE ; 
 int GLOB_STAR ; 
 int /*<<< orphan*/  STRglobdot ; 
 int /*<<< orphan*/  STRglobstar ; 
 int /*<<< orphan*/  STRnonomatch ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** blk2short (scalar_t__) ; 
 int glob (char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  setname (char*) ; 
 char* short2qstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderror (int) ; 

__attribute__((used)) static Char **
libglob(Char **vl)
{
    int     gflgs = GLOB_QUOTE | GLOB_NOMAGIC | GLOB_ALTNOT;
    glob_t  globv;
    char   *ptr;
    int     nonomatch = adrof(STRnonomatch) != 0, magic = 0, match = 0;

    if (adrof(STRglobdot))
       gflgs |= GLOB_DOT;

    if (adrof(STRglobstar))
       gflgs |= GLOB_STAR;

    if (!vl || !vl[0])
	return(vl);

    globv.gl_offs = 0;
    globv.gl_pathv = 0;
    globv.gl_pathc = 0;

    if (nonomatch)
	gflgs |= GLOB_NOCHECK;

    do {
	ptr = short2qstr(*vl);
	switch (glob(ptr, gflgs, 0, &globv)) {
	case GLOB_ABEND:
	    globfree(&globv);
	    setname(ptr);
	    stderror(ERR_NAME | ERR_GLOB);
	    /* NOTREACHED */
	case GLOB_NOSPACE:
	    globfree(&globv);
	    stderror(ERR_NOMEM);
	    /* NOTREACHED */
	default:
	    break;
	}
	if (globv.gl_flags & GLOB_MAGCHAR) {
	    match |= (globv.gl_matchc != 0);
	    magic = 1;
	}
	gflgs |= GLOB_APPEND;
    }
    while (*++vl);
    vl = (globv.gl_pathc == 0 || (magic && !match && !nonomatch)) ? 
	NULL : blk2short(globv.gl_pathv);
    globfree(&globv);
    return (vl);
}