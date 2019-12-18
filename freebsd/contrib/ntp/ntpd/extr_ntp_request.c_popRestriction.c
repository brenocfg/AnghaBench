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
typedef  int /*<<< orphan*/  restrict_u ;
struct TYPE_5__ {scalar_t__ fcnt; struct TYPE_5__* link; int /*<<< orphan*/ ** pres; } ;
typedef  TYPE_1__ RestrictStackT ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ getStackSheetSize (TYPE_1__*) ; 

__attribute__((used)) static int/*BOOL*/
popRestriction(
	RestrictStackT   **spp,
	const restrict_u **opp
	)
{
	RestrictStackT *sp;

	if (NULL == (sp = *spp) || sp->fcnt >= getStackSheetSize(sp))
		return FALSE;
	
	*opp = sp->pres[sp->fcnt++];
	if (sp->fcnt >= getStackSheetSize(sp)) {
		/* discard sheet from scratch pad */
		*spp = sp->link;
		free(sp);
	}
	return TRUE;
}