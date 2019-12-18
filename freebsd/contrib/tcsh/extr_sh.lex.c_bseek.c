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
struct Ain {scalar_t__ f_seek; int /*<<< orphan*/  c_seek; int /*<<< orphan*/  a_seek; scalar_t__ type; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
#define  TCSH_A_SEEK 130 
#define  TCSH_E_SEEK 129 
#define  TCSH_F_SEEK 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  alvec ; 
 int /*<<< orphan*/  alvecp ; 
 scalar_t__ aret ; 
 int /*<<< orphan*/  cantell ; 
 int /*<<< orphan*/  evalp ; 
 int /*<<< orphan*/  evalvec ; 
 scalar_t__ fbobp ; 
 scalar_t__* fclens ; 
 scalar_t__ feobp ; 
 scalar_t__ fseekp ; 
 int /*<<< orphan*/  xprintf (int /*<<< orphan*/ ,scalar_t__,...) ; 

void
bseek(struct Ain *l)
{
    switch (aret = l->type) {
    case TCSH_E_SEEK:
	evalvec = l->a_seek;
	evalp = l->c_seek;
#ifdef DEBUG_SEEK
	xprintf(CGETS(16, 4, "seek to eval %x %x\n"), evalvec, evalp);
#endif
	return;
    case TCSH_A_SEEK:
	alvec = l->a_seek;
	alvecp = l->c_seek;
#ifdef DEBUG_SEEK
	xprintf(CGETS(16, 5, "seek to alias %x %x\n"), alvec, alvecp);
#endif
	return;
    case TCSH_F_SEEK:	
#ifdef DEBUG_SEEK
	xprintf(CGETS(16, 6, "seek to file %x\n"), fseekp);
#endif
	fseekp = l->f_seek;
#ifdef WIDE_STRINGS
	if (cantell) {
	    if (fseekp >= fbobp && feobp >= fbobp) {
		size_t i;
		off_t o;

		o = fbobp;
		for (i = 0; i < (size_t)(feobp - fbobp); i++) {
		    if (fseekp == o) {
			fseekp = fbobp + i;
			return;
		    }
		    o += fclens[i];
		}
		if (fseekp == o) {
		    fseekp = feobp;
		    return;
		}
	    }
	    fbobp = feobp = fseekp + 1; /* To force lseek() */
	}
#endif
	return;
    default:
	xprintf(CGETS(16, 7, "Bad seek type %d\n"), aret);
	abort();
    }
}