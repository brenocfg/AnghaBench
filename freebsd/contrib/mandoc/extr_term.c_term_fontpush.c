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
struct termp {int fontl; int* fontq; size_t fonti; size_t fontsz; } ;
typedef  enum termfont { ____Placeholder_termfont } termfont ;

/* Variables and functions */
 int* mandoc_reallocarray (int*,int,int) ; 

void
term_fontpush(struct termp *p, enum termfont f)
{

	p->fontl = p->fontq[p->fonti];
	if (++p->fonti == p->fontsz) {
		p->fontsz += 8;
		p->fontq = mandoc_reallocarray(p->fontq,
		    p->fontsz, sizeof(*p->fontq));
	}
	p->fontq[p->fonti] = f;
}