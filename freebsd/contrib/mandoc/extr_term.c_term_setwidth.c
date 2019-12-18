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
struct termp {int /*<<< orphan*/  (* setwidth ) (struct termp*,int,int) ;} ;
struct roffsu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALE_MAX ; 
 int /*<<< orphan*/ * a2roffsu (char const*,struct roffsu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct termp*,int,int) ; 
 int term_hspan (struct termp*,struct roffsu*) ; 

void
term_setwidth(struct termp *p, const char *wstr)
{
	struct roffsu	 su;
	int		 iop, width;

	iop = 0;
	width = 0;
	if (NULL != wstr) {
		switch (*wstr) {
		case '+':
			iop = 1;
			wstr++;
			break;
		case '-':
			iop = -1;
			wstr++;
			break;
		default:
			break;
		}
		if (a2roffsu(wstr, &su, SCALE_MAX) != NULL)
			width = term_hspan(p, &su);
		else
			iop = 0;
	}
	(*p->setwidth)(p, iop, width);
}