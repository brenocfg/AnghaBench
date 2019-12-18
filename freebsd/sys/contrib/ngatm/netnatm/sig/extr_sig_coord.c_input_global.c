#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uni_msg {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  flag; } ;
struct TYPE_4__ {TYPE_3__ cref; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
struct uni_all {int mtype; TYPE_2__ u; } ;
struct uni {int /*<<< orphan*/  glob_respond; int /*<<< orphan*/  glob_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGR_RESTART ; 
 int /*<<< orphan*/  SIGR_STATUS ; 
 int /*<<< orphan*/  SIGS_RESTART_ACK ; 
 int /*<<< orphan*/  SIGS_STATUS ; 
 int /*<<< orphan*/  UNI_CAUSE_CREF_INV ; 
 int /*<<< orphan*/  UNI_FAC_COORD ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
#define  UNI_RESTART 130 
#define  UNI_RESTART_ACK 129 
#define  UNI_STATUS 128 
 int /*<<< orphan*/  VERBOSE (struct uni*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  uni_enq_resp (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  uni_enq_start (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_respond_status (struct uni*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
input_global(struct uni *uni, struct uni_msg *m, struct uni_all *u)
{
	VERBOSE(uni, UNI_FAC_COORD, 2, "GLOB MTYPE = %x", u->mtype);

	switch (u->mtype) {

	  default:
		/*
		 * Q.2931:Coord-U 7/10
		 * Q.2931: 5.6.3.2e
		 * Amd4:   29e
		 */
		uni_respond_status(uni, &u->u.hdr.cref,
		    u->u.hdr.cref.flag ? uni->glob_start : uni->glob_respond,
		    UNI_CAUSE_CREF_INV);
		break;

	  case UNI_RESTART:
		if (u->u.hdr.cref.flag) {
			/*
			 * Q.2931:Coord-U 7/10 (5.6.3.2h)
			 */
			uni_respond_status(uni, &u->u.hdr.cref,
			    uni->glob_start, UNI_CAUSE_CREF_INV);
			break;
		}
		uni_enq_resp(uni, SIGR_RESTART, 0, m, u);
		return;

	  case UNI_RESTART_ACK:
		if (!u->u.hdr.cref.flag) {
			/*
			 * Q.2931:Coord-U 7/10 (5.6.3.2h)
			 * Note, that the SDL diagram contains an error.
			 * The error with the 'YES' label should go to the
			 * box below 'OTHER'.
			 */
			uni_respond_status(uni, &u->u.hdr.cref,
			    uni->glob_respond, UNI_CAUSE_CREF_INV);
			break;
		}
		uni_enq_start(uni, SIGS_RESTART_ACK, 0, m, u);
		return;

	  case UNI_STATUS:
		if (u->u.hdr.cref.flag)
			uni_enq_start(uni, SIGS_STATUS, 0, m, u);
		else
			uni_enq_resp(uni, SIGR_STATUS, 0, m, u);
		return;
	}
	uni_msg_destroy(m);
	UNI_FREE(u);
}