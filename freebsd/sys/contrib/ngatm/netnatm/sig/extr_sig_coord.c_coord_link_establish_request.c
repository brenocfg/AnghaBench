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
typedef  int /*<<< orphan*/  uint32_t ;
struct uni {int custat; int /*<<< orphan*/  arg; TYPE_1__* funcs; int /*<<< orphan*/  timer309; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* uni_output ) (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* saal_output ) (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ,char*) ; 
#define  CU_STAT0 131 
#define  CU_STAT1 130 
#define  CU_STAT2 129 
#define  CU_STAT3 128 
 int /*<<< orphan*/  SAAL_ESTABLISH_request ; 
 int /*<<< orphan*/  SIGO_LINK_ESTABLISH_request ; 
 int /*<<< orphan*/  TIMER_ISACT (struct uni*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_START_UNI (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIAPI_ERROR_BAD_CALLSTATE ; 
 int /*<<< orphan*/  UNIAPI_LINK_ESTABLISH_confirm ; 
 int /*<<< orphan*/  UNIAPI_OK ; 
 int /*<<< orphan*/  UNI_FAC_COORD ; 
 int /*<<< orphan*/  VERBOSE0 (struct uni*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_custat (struct uni*,int) ; 
 int /*<<< orphan*/  stub1 (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t309 ; 
 int /*<<< orphan*/  uni_delenq_coord (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uniapi_uni_error (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
coord_link_establish_request(struct uni *uni, uint32_t cookie)
{
	switch (uni->custat) {

	  case CU_STAT0:
		/*
		 * Q.2931:Coord-U 4/10
		 */
		uni->funcs->saal_output(uni, uni->arg,
		    SAAL_ESTABLISH_request, NULL);
		if (!TIMER_ISACT(uni, t309))
			TIMER_START_UNI(uni, t309, uni->timer309);
		set_custat(uni, CU_STAT1);
		if (cookie)
			uniapi_uni_error(uni, UNIAPI_OK, cookie, 0);
		break;

	  case CU_STAT1:
		/*
		 * Q.2931:Coord-U 4/10
		 * This is probably missing from the delay field.
		 */
		uni_delenq_coord(uni, SIGO_LINK_ESTABLISH_request,
		    cookie, NULL);
		break;

	  case CU_STAT2:
		uniapi_uni_error(uni, UNIAPI_ERROR_BAD_CALLSTATE, cookie, 0);
		if (cookie == 0)
			VERBOSE0(uni, UNI_FAC_COORD,
			    "signal link-establish.request in CU%u",
			    uni->custat);
		break;

	  case CU_STAT3:
		/*
		 * Q.2931:Coord-U 5/10
		 */
		uni->funcs->uni_output(uni, uni->arg,
		    UNIAPI_LINK_ESTABLISH_confirm, 0, NULL);
		uniapi_uni_error(uni, UNIAPI_OK, cookie, 0);
		break;

	  default:
		ASSERT(0, ("CU_STAT*"));
	}
}