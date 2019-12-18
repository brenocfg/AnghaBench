#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mparse {TYPE_4__* man; TYPE_1__* primary; int /*<<< orphan*/  roff; } ;
struct TYPE_7__ {TYPE_2__* first; int /*<<< orphan*/  macroset; } ;
struct TYPE_8__ {TYPE_3__ meta; int /*<<< orphan*/ * manmac; int /*<<< orphan*/ * mdocmac; } ;
struct TYPE_6__ {int /*<<< orphan*/  tok; } ;
struct TYPE_5__ {char* buf; int sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACROSET_MAN ; 
 int /*<<< orphan*/  MACROSET_MDOC ; 
 int /*<<< orphan*/  MAN_MAX ; 
 int /*<<< orphan*/  MAN_TH ; 
 int /*<<< orphan*/  MDOC_Dd ; 
 int /*<<< orphan*/  MDOC_MAX ; 
 int MPARSE_MAN ; 
 int MPARSE_MDOC ; 
 int /*<<< orphan*/  TOKEN_NONE ; 
 char* memchr (char*,char,int) ; 
 int roff_getformat (int /*<<< orphan*/ ) ; 
 void* roffhash_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
choose_parser(struct mparse *curp)
{
	char		*cp, *ep;
	int		 format;

	/*
	 * If neither command line arguments -mdoc or -man select
	 * a parser nor the roff parser found a .Dd or .TH macro
	 * yet, look ahead in the main input buffer.
	 */

	if ((format = roff_getformat(curp->roff)) == 0) {
		cp = curp->primary->buf;
		ep = cp + curp->primary->sz;
		while (cp < ep) {
			if (*cp == '.' || *cp == '\'') {
				cp++;
				if (cp[0] == 'D' && cp[1] == 'd') {
					format = MPARSE_MDOC;
					break;
				}
				if (cp[0] == 'T' && cp[1] == 'H') {
					format = MPARSE_MAN;
					break;
				}
			}
			cp = memchr(cp, '\n', ep - cp);
			if (cp == NULL)
				break;
			cp++;
		}
	}

	if (format == MPARSE_MDOC) {
		curp->man->meta.macroset = MACROSET_MDOC;
		if (curp->man->mdocmac == NULL)
			curp->man->mdocmac = roffhash_alloc(MDOC_Dd, MDOC_MAX);
	} else {
		curp->man->meta.macroset = MACROSET_MAN;
		if (curp->man->manmac == NULL)
			curp->man->manmac = roffhash_alloc(MAN_TH, MAN_MAX);
	}
	curp->man->meta.first->tok = TOKEN_NONE;
}