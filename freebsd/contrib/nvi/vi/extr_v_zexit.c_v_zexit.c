#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VICMD ;
struct TYPE_7__ {int /*<<< orphan*/  ep; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  FS_ALL ; 
 scalar_t__ F_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_MODIFIED ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_EXIT ; 
 scalar_t__ ex_ncheck (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_m3 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_write (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
v_zexit(SCR *sp, VICMD *vp)
{
	/* Write back any modifications. */
	if (F_ISSET(sp->ep, F_MODIFIED) &&
	    file_write(sp, NULL, NULL, NULL, FS_ALL))
		return (1);

	/* Check to make sure it's not a temporary file. */
	if (file_m3(sp, 0))
		return (1);

	/* Check for more files to edit. */
	if (ex_ncheck(sp, 0))
		return (1);

	F_SET(sp, SC_EXIT);
	return (0);
}