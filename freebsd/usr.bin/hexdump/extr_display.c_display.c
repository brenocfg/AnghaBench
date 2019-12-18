#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  char* quad_t ;
typedef  scalar_t__ off_t ;
struct TYPE_11__ {TYPE_1__* nextpr; } ;
struct TYPE_10__ {TYPE_2__* nextfu; struct TYPE_10__* nextfs; } ;
struct TYPE_9__ {int flags; int reps; TYPE_1__* nextpr; struct TYPE_9__* nextfu; } ;
struct TYPE_8__ {scalar_t__ bcnt; int flags; char* nospace; char* fmt; struct TYPE_8__* nextpr; } ;
typedef  TYPE_1__ PR ;
typedef  TYPE_2__ FU ;
typedef  TYPE_3__ FS ;

/* Variables and functions */
#define  F_ADDRESS 129 
 int F_BPAD ; 
 int F_IGNORE ; 
#define  F_TEXT 128 
 scalar_t__ address ; 
 int /*<<< orphan*/  bpad (TYPE_1__*) ; 
 scalar_t__ eaddress ; 
 TYPE_6__* endfu ; 
 TYPE_3__* fshead ; 
 char* get () ; 
 int /*<<< orphan*/  print (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
display(void)
{
	FS *fs;
	FU *fu;
	PR *pr;
	int cnt;
	u_char *bp;
	off_t saveaddress;
	u_char savech, *savebp;

	savech = 0;
	while ((bp = get()))
	    for (fs = fshead, savebp = bp, saveaddress = address; fs;
		fs = fs->nextfs, bp = savebp, address = saveaddress)
		    for (fu = fs->nextfu; fu; fu = fu->nextfu) {
			if (fu->flags&F_IGNORE)
				break;
			for (cnt = fu->reps; cnt; --cnt)
			    for (pr = fu->nextpr; pr; address += pr->bcnt,
				bp += pr->bcnt, pr = pr->nextpr) {
				    if (eaddress && address >= eaddress &&
					!(pr->flags & (F_TEXT|F_BPAD)))
					    bpad(pr);
				    if (cnt == 1 && pr->nospace) {
					savech = *pr->nospace;
					*pr->nospace = '\0';
				    }
				    print(pr, bp);
				    if (cnt == 1 && pr->nospace)
					*pr->nospace = savech;
			    }
		    }
	if (endfu) {
		/*
		 * If eaddress not set, error or file size was multiple of
		 * blocksize, and no partial block ever found.
		 */
		if (!eaddress) {
			if (!address)
				return;
			eaddress = address;
		}
		for (pr = endfu->nextpr; pr; pr = pr->nextpr)
			switch(pr->flags) {
			case F_ADDRESS:
				(void)printf(pr->fmt, (quad_t)eaddress);
				break;
			case F_TEXT:
				(void)printf("%s", pr->fmt);
				break;
			}
	}
}