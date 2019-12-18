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
typedef  scalar_t__ u_long ;
struct verslist {scalar_t__ vers; struct verslist* next; } ;
struct rpcbdump_short {struct verslist* vlist; } ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static bool_t
add_version(struct rpcbdump_short *rs, u_long vers)
{
	struct verslist *vl;

	for (vl = rs->vlist; vl; vl = vl->next)
		if (vl->vers == vers)
			break;
	if (vl)
		return (TRUE);
	vl = (struct verslist *)malloc(sizeof (struct verslist));
	if (vl == NULL)
		return (FALSE);
	vl->vers = vers;
	vl->next = rs->vlist;
	rs->vlist = vl;
	return (TRUE);
}