#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct termp {int flags; int col; TYPE_1__* tcol; int /*<<< orphan*/  (* letter ) (struct termp*,char) ;} ;
struct TYPE_2__ {int maxcols; int lastcol; char* buf; } ;

/* Variables and functions */
 char ASCII_NBRSP ; 
 int TERMP_NOBUF ; 
 int /*<<< orphan*/  adjbuf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (struct termp*,char) ; 

__attribute__((used)) static void
bufferc(struct termp *p, char c)
{
	if (p->flags & TERMP_NOBUF) {
		(*p->letter)(p, c);
		return;
	}
	if (p->col + 1 >= p->tcol->maxcols)
		adjbuf(p->tcol, p->col + 1);
	if (p->tcol->lastcol <= p->col || (c != ' ' && c != ASCII_NBRSP))
		p->tcol->buf[p->col] = c;
	if (p->tcol->lastcol < ++p->col)
		p->tcol->lastcol = p->col;
}