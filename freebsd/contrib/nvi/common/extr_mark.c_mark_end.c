#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  marks; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  LMARK ;
typedef  TYPE_1__ EXF ;

/* Variables and functions */
 int /*<<< orphan*/ * SLIST_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  q ; 

int
mark_end(
	SCR *sp,
	EXF *ep)
{
	LMARK *lmp;

	/*
	 * !!!
	 * ep MAY NOT BE THE SAME AS sp->ep, DON'T USE THE LATTER.
	 */
	while ((lmp = SLIST_FIRST(ep->marks)) != NULL) {
		SLIST_REMOVE_HEAD(ep->marks, q);
		free(lmp);
	}
	return (0);
}