#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* seq ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int) ;} ;
struct TYPE_7__ {char* data; int size; } ;
typedef  TYPE_1__ DBT ;
typedef  TYPE_2__ DB ;

/* Variables and functions */
 int R_FIRST ; 
 int R_LAST ; 
 int R_NEXT ; 
 int R_PREV ; 
 int R_RNEXT ; 
 int R_RPREV ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  ofd ; 
 int stub1 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
dump(DB *dbp, int rev, int recurse)
{
	DBT key, data;
	int xflags, nflags;

	if (rev) {
		xflags = R_LAST;
#ifdef __NetBSD__
		nflags = recurse ? R_RPREV : R_PREV;
#else
		nflags = R_PREV;
#endif
	} else {
		xflags = R_FIRST;
#ifdef __NetBSD__
		nflags = recurse ? R_RNEXT : R_NEXT;
#else
		nflags = R_NEXT;
#endif
	}
	for (;; xflags = nflags)
		switch (dbp->seq(dbp, &key, &data, xflags)) {
		case 0:
			(void)write(ofd, data.data, data.size);
			if (ofd == STDOUT_FILENO)
				(void)write(ofd, "\n", 1);
			break;
		case 1:
			goto done;
		case -1:
			err(1, "line %zu: (dump) seq failed", lineno);
			/* NOTREACHED */
		}
done:	return;
}