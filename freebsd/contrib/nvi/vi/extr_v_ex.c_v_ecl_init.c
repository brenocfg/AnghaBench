#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ep; } ;
struct TYPE_11__ {TYPE_6__* ccl_sp; } ;
struct TYPE_10__ {TYPE_2__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ GS ;
typedef  int /*<<< orphan*/  FREF ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_RCV_ON ; 
 int /*<<< orphan*/ * file_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ file_init (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_end (TYPE_6__*) ; 
 scalar_t__ screen_init (TYPE_2__*,TYPE_1__*,TYPE_6__**) ; 

__attribute__((used)) static int
v_ecl_init(SCR *sp)
{
	FREF *frp;
	GS *gp;

	gp = sp->gp;

	/* Get a temporary file. */
	if ((frp = file_add(sp, NULL)) == NULL)
		return (1);

	/*
	 * XXX
	 * Create a screen -- the file initialization code wants one.
	 */
	if (screen_init(gp, sp, &gp->ccl_sp))
		return (1);
	if (file_init(gp->ccl_sp, frp, NULL, 0)) {
		(void)screen_end(gp->ccl_sp);
		gp->ccl_sp = NULL;
		return (1);
	}

	/* The underlying file isn't recoverable. */
	F_CLR(gp->ccl_sp->ep, F_RCV_ON);

	return (0);
}