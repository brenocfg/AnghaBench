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
struct entry {int e_type; struct entry* e_links; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 long FAIL ; 
 long GOOD ; 
 int LEAF ; 
 int /*<<< orphan*/  badentry (struct entry*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct entry* lookupino (scalar_t__) ; 
 struct entry* lookupname (char*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

long
verifyfile(char *name, ino_t ino, int type)
{
	struct entry *np, *ep;
	long descend = GOOD;

	ep = lookupname(name);
	if (ep == NULL) {
		fprintf(stderr, "Warning: missing name %s\n", name);
		return (FAIL);
	}
	np = lookupino(ino);
	if (np != ep)
		descend = FAIL;
	for ( ; np != NULL; np = np->e_links)
		if (np == ep)
			break;
	if (np == NULL)
		panic("missing inumber %ju\n", (uintmax_t)ino);
	if (ep->e_type == LEAF && type != LEAF)
		badentry(ep, "type should be LEAF");
	return (descend);
}