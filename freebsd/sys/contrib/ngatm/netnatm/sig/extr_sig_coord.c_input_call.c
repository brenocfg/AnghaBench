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
struct uni_msg {int dummy; } ;
struct uni_all {int mtype; } ;
struct call {scalar_t__ mine; int /*<<< orphan*/  cref; int /*<<< orphan*/  uni; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGC_ADD_PARTY ; 
 int /*<<< orphan*/  SIGC_ADD_PARTY_ACK ; 
 int /*<<< orphan*/  SIGC_ADD_PARTY_REJ ; 
 int /*<<< orphan*/  SIGC_ALERTING ; 
 int /*<<< orphan*/  SIGC_CALL_PROC ; 
 int /*<<< orphan*/  SIGC_CONNECT ; 
 int /*<<< orphan*/  SIGC_CONNECT_ACK ; 
 int /*<<< orphan*/  SIGC_DROP_PARTY ; 
 int /*<<< orphan*/  SIGC_DROP_PARTY_ACK ; 
 int /*<<< orphan*/  SIGC_NOTIFY ; 
 int /*<<< orphan*/  SIGC_PARTY_ALERTING ; 
 int /*<<< orphan*/  SIGC_RELEASE ; 
 int /*<<< orphan*/  SIGC_RELEASE_COMPL ; 
 int /*<<< orphan*/  SIGC_STATUS ; 
 int /*<<< orphan*/  SIGC_STATUS_ENQ ; 
 int /*<<< orphan*/  SIGC_UNKNOWN ; 
#define  UNI_ADD_PARTY 143 
#define  UNI_ADD_PARTY_ACK 142 
#define  UNI_ADD_PARTY_REJ 141 
#define  UNI_ALERTING 140 
#define  UNI_CALL_PROC 139 
#define  UNI_CONNECT 138 
#define  UNI_CONNECT_ACK 137 
#define  UNI_DROP_PARTY 136 
#define  UNI_DROP_PARTY_ACK 135 
 int /*<<< orphan*/  UNI_FAC_COORD ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
#define  UNI_NOTIFY 134 
#define  UNI_PARTY_ALERTING 133 
#define  UNI_RELEASE 132 
#define  UNI_RELEASE_COMPL 131 
#define  UNI_SETUP 130 
#define  UNI_STATUS 129 
#define  UNI_STATUS_ENQ 128 
 int /*<<< orphan*/  VERBOSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uni_enq_call (struct call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 

__attribute__((used)) static void
input_call(struct call *c, struct uni_msg *m, struct uni_all *u)
{
	VERBOSE(c->uni, UNI_FAC_COORD, 2, "CALL MTYPE = %x %d/%s", 
		u->mtype, c->cref, c->mine ? "mine":"his");

	switch (u->mtype) {

	  case UNI_SETUP:
		/*
		 * Ignored
		 */
		break;

	  case UNI_CALL_PROC:
		uni_enq_call(c, SIGC_CALL_PROC, 0, m, u);
		return;

	  case UNI_ALERTING:
		uni_enq_call(c, SIGC_ALERTING, 0, m, u);
		return;

	  case UNI_RELEASE:
		uni_enq_call(c, SIGC_RELEASE, 0, m, u);
		return;

	  case UNI_RELEASE_COMPL:
		uni_enq_call(c, SIGC_RELEASE_COMPL, 0, m, u);
		return;

	  case UNI_CONNECT:
		uni_enq_call(c, SIGC_CONNECT, 0, m, u);
		return;

	  case UNI_CONNECT_ACK:
		uni_enq_call(c, SIGC_CONNECT_ACK, 0, m, u);
		return;

	  case UNI_NOTIFY:
		uni_enq_call(c, SIGC_NOTIFY, 0, m, u);
		return;

	  case UNI_STATUS:
		uni_enq_call(c, SIGC_STATUS, 0, m, u);
		return;

	  case UNI_STATUS_ENQ:
		uni_enq_call(c, SIGC_STATUS_ENQ, 0, m, u);
		return;

	  case UNI_ADD_PARTY:
		uni_enq_call(c, SIGC_ADD_PARTY, 0, m, u);
		return;

	  case UNI_PARTY_ALERTING:
		uni_enq_call(c, SIGC_PARTY_ALERTING, 0, m, u);
		return;

	  case UNI_ADD_PARTY_ACK:
		uni_enq_call(c, SIGC_ADD_PARTY_ACK, 0, m, u);
		return;

	  case UNI_ADD_PARTY_REJ:
		uni_enq_call(c, SIGC_ADD_PARTY_REJ, 0, m, u);
		return;

	  case UNI_DROP_PARTY:
		uni_enq_call(c, SIGC_DROP_PARTY, 0, m, u);
		return;

	  case UNI_DROP_PARTY_ACK:
		uni_enq_call(c, SIGC_DROP_PARTY_ACK, 0, m, u);
		return;

	  default:
		uni_enq_call(c, SIGC_UNKNOWN, 0, m, u);
		return;
	}
	UNI_FREE(u);
	uni_msg_destroy(m);
}