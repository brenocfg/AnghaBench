#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int refcnt; } ;
struct TYPE_5__ {int /*<<< orphan*/  frp; TYPE_2__* ep; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXF ;

/* Variables and functions */
 int /*<<< orphan*/  FR_TMPEXIT ; 
 scalar_t__ F_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

int
file_m3(
	SCR *sp,
	int force)
{
	EXF *ep;

	ep = sp->ep;

	/* If no file loaded, return no modifications. */
	if (ep == NULL)
		return (0);

	/*
	 * Don't exit while in a temporary files if the file was ever modified.
	 * The problem is that if the user does a ":wq", we write and quit,
	 * unlinking the temporary file.  Not what the user had in mind at all.
	 * We permit writing to temporary files, so that user maps using file
	 * system names work with temporary files.
	 */
	if (F_ISSET(sp->frp, FR_TMPEXIT) && ep->refcnt <= 1 && !force) {
		msgq(sp, M_ERR,
		    "265|File is a temporary; exit will discard modifications");
		return (1);
	}
	return (0);
}