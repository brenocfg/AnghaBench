#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uschar ;
struct TYPE_5__ {int initstat; int** gototab; scalar_t__* out; scalar_t__ reset; } ;
typedef  TYPE_1__ fa ;

/* Variables and functions */
 int cgoto (TYPE_1__*,int,size_t) ; 
 int makeinit (TYPE_1__*,int /*<<< orphan*/ ) ; 

int match(fa *f, const char *p0)	/* shortest match ? */
{
	int s, ns;
	uschar *p = (uschar *) p0;

	s = f->reset ? makeinit(f,0) : f->initstat;
	if (f->out[s])
		return(1);
	do {
		/* assert(*p < NCHARS); */
		if ((ns = f->gototab[s][*p]) != 0)
			s = ns;
		else
			s = cgoto(f, s, *p);
		if (f->out[s])
			return(1);
	} while (*p++ != 0);
	return(0);
}