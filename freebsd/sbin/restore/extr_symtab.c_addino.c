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
typedef  int /*<<< orphan*/  uintmax_t ;
struct entry {size_t e_ino; struct entry* e_next; } ;
typedef  size_t ino_t ;

/* Variables and functions */
 size_t UFS_WINO ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 scalar_t__ dflag ; 
 struct entry** entry ; 
 size_t entrytblsize ; 
 size_t maxino ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
addino(ino_t inum, struct entry *np)
{
	struct entry **epp;

	if (inum < UFS_WINO || inum >= maxino)
		panic("addino: out of range %ju\n", (uintmax_t)inum);
	epp = &entry[inum % entrytblsize];
	np->e_ino = inum;
	np->e_next = *epp;
	*epp = np;
	if (dflag)
		for (np = np->e_next; np != NULL; np = np->e_next)
			if (np->e_ino == inum)
				badentry(np, "duplicate inum");
}