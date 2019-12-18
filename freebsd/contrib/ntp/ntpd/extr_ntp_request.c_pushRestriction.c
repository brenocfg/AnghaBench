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
struct TYPE_5__ {size_t fcnt; int /*<<< orphan*/  const** pres; struct TYPE_5__* link; } ;
typedef  TYPE_1__ RestrictStackT ;

/* Variables and functions */
 int TRUE ; 
 TYPE_1__* emalloc (int) ; 
 size_t getStackSheetSize (TYPE_1__*) ; 

__attribute__((used)) static int/*BOOL*/
pushRestriction(
	RestrictStackT  **spp,
	const restrict_u *ptr
	)
{
	RestrictStackT *sp;

	if (NULL == (sp = *spp) || 0 == sp->fcnt) {
		/* need another sheet in the scratch pad */
		sp = emalloc(sizeof(*sp));
		sp->link = *spp;
		sp->fcnt = getStackSheetSize(sp);
		*spp = sp;
	}
	sp->pres[--sp->fcnt] = ptr;
	return TRUE;
}