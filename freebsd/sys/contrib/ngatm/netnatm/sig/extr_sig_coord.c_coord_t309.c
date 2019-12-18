#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uni {int custat; int /*<<< orphan*/  arg; TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* uni_output ) (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ,char*) ; 
#define  CU_STAT0 131 
#define  CU_STAT1 130 
#define  CU_STAT2 129 
#define  CU_STAT3 128 
 int /*<<< orphan*/  SIGC_LINK_ESTABLISH_ERROR_indication ; 
 int /*<<< orphan*/  UNIAPI_LINK_RELEASE_confirm ; 
 int /*<<< orphan*/  UNI_FAC_COORD ; 
 int /*<<< orphan*/  VERBOSE0 (struct uni*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_custat (struct uni*,int const) ; 
 int /*<<< orphan*/  sig_all_calls (struct uni*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
coord_t309(struct uni *uni)
{
	switch (uni->custat) {

	  case CU_STAT0:
	  case CU_STAT1:
		/*
		 * Q.2931:Coord-U 4/10
		 */
		sig_all_calls(uni, SIGC_LINK_ESTABLISH_ERROR_indication);
		set_custat(uni, CU_STAT0);
		/* this is not in the SDLs, but how will the call control
		 * know, that starting the LINK has failed otherwise? */
		uni->funcs->uni_output(uni, uni->arg,
		    UNIAPI_LINK_RELEASE_confirm, 0, NULL);
		break;

	  case CU_STAT2:
	  case CU_STAT3:
		VERBOSE0(uni, UNI_FAC_COORD,
		    "signal T309 in CU%u", uni->custat);
		break;

	  default:
		ASSERT(0, ("CU_STAT*"));
	}
}