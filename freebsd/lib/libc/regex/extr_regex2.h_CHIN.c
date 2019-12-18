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
typedef  int wint_t ;
struct TYPE_4__ {int* bmp; int invert; scalar_t__ icase; } ;
typedef  TYPE_1__ cset ;

/* Variables and functions */
 int CHIN1 (TYPE_1__*,int) ; 
 int NC ; 
 int /*<<< orphan*/  assert (int) ; 
 int towlower (int) ; 
 int towupper (int) ; 

__attribute__((used)) static __inline int
CHIN(cset *cs, wint_t ch)
{

	assert(ch >= 0);
	if (ch < NC)
		return (((cs->bmp[ch >> 3] & (1 << (ch & 7))) != 0) ^
		    cs->invert);
	else if (cs->icase)
		return (CHIN1(cs, ch) || CHIN1(cs, towlower(ch)) ||
		    CHIN1(cs, towupper(ch)));
	else
		return (CHIN1(cs, ch));
}