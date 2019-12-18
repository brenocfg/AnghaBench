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
typedef  int wint_t ;
struct parse {int dummy; } ;
struct TYPE_3__ {int* bmp; int* wides; scalar_t__ icase; scalar_t__ nwides; } ;
typedef  TYPE_1__ cset ;

/* Variables and functions */
 int NC ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  SETERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* reallocarray (int*,scalar_t__,int) ; 
 int towlower (int) ; 
 int towupper (int) ; 

__attribute__((used)) static void
CHadd(struct parse *p, cset *cs, wint_t ch)
{
	wint_t nch, *newwides;
	assert(ch >= 0);
	if (ch < NC)
		cs->bmp[ch >> 3] |= 1 << (ch & 7);
	else {
		newwides = reallocarray(cs->wides, cs->nwides + 1,
		    sizeof(*cs->wides));
		if (newwides == NULL) {
			SETERROR(REG_ESPACE);
			return;
		}
		cs->wides = newwides;
		cs->wides[cs->nwides++] = ch;
	}
	if (cs->icase) {
		if ((nch = towlower(ch)) < NC)
			cs->bmp[nch >> 3] |= 1 << (nch & 7);
		if ((nch = towupper(ch)) < NC)
			cs->bmp[nch >> 3] |= 1 << (nch & 7);
	}
}