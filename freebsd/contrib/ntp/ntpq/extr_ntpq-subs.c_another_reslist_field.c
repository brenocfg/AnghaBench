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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {char* hits; int /*<<< orphan*/  idx; int /*<<< orphan*/  flagstr; int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ reslist_row ;
typedef  int /*<<< orphan*/  addrmaskstr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int RESLIST_FIELDS ; 
 int /*<<< orphan*/  ZERO (TYPE_1__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int sockaddr_masktoprefixlen (int /*<<< orphan*/ *) ; 
 char* stoa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
another_reslist_field(
	int *		pfields,
	reslist_row *	prow,
	FILE *		fp
	)
{
	char	addrmaskstr[128];
	int	prefix;	/* subnet mask as prefix bits count */
	u_int	idx;

	(*pfields)++;
	/* we understand 4 tags */
	if (RESLIST_FIELDS > *pfields)
		return;

	prefix = sockaddr_masktoprefixlen(&prow->mask);
	if (prefix >= 0)
		snprintf(addrmaskstr, sizeof(addrmaskstr), "%s/%d",
			 stoa(&prow->addr), prefix);
	else
		snprintf(addrmaskstr, sizeof(addrmaskstr), "%s %s",
			 stoa(&prow->addr), stoa(&prow->mask));

	/*
	"   hits    addr/prefix or addr mask\n"
	"           restrictions\n"
	"==============================================================================\n");
	 */
	fprintf(fp,
		"%10lu %s\n"
		"           %s\n",
		prow->hits, addrmaskstr, prow->flagstr);
	idx = prow->idx;
	ZERO(*prow);
	prow->idx = idx;
}