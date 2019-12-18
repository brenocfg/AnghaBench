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
typedef  union uni_msgall {int dummy; } uni_msgall ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {scalar_t__ present; } ;
struct TYPE_5__ {TYPE_1__ h; } ;
struct unicx {int ielast; TYPE_2__ repeat; } ;
struct uni_msg {int /*<<< orphan*/ * b_rptr; int /*<<< orphan*/ * b_wptr; } ;
struct uni_iehdr {int /*<<< orphan*/  act; int /*<<< orphan*/  present; int /*<<< orphan*/  coding; } ;
struct iedecl {int maxlen; int flags; } ;
typedef  enum uni_msgtype { ____Placeholder_uni_msgtype } uni_msgtype ;
typedef  enum uni_ietype { ____Placeholder_uni_ietype } uni_ietype ;
struct TYPE_6__ {int (* decode ) (union uni_msgall*,struct uni_msg*,int,struct uni_iehdr*,int,struct unicx*) ;} ;

/* Variables and functions */
#define  DEC_ERR 130 
#define  DEC_ILL 129 
#define  DEC_OK 128 
 struct iedecl* GET_IEDECL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANIC (char*) ; 
 int UNIFL_ACCESS ; 
 int /*<<< orphan*/  UNI_IERR_ACC ; 
 int /*<<< orphan*/  UNI_IERR_BAD ; 
 int /*<<< orphan*/  UNI_IERR_UNK ; 
 int /*<<< orphan*/  UNI_IE_ERROR ; 
 int UNI_IE_REPEAT ; 
 int UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_SAVE_IERR (struct unicx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int stub1 (union uni_msgall*,struct uni_msg*,int,struct uni_iehdr*,int,struct unicx*) ; 
 scalar_t__ uni_decode_ie_hdr (int*,struct uni_iehdr*,struct uni_msg*,struct unicx*,int*) ; 
 int uni_msg_len (struct uni_msg*) ; 
 TYPE_3__** uni_msgtable ; 

__attribute__((used)) static int
uni_decode_body_internal(enum uni_msgtype mtype, struct uni_msg *msg,
    union uni_msgall *out, struct unicx *cx)
{
	enum uni_ietype ietype;
	struct uni_iehdr hdr;
	u_int ielen;
	const struct iedecl *iedecl;
	int err = 0, ret;
	u_char *end;

	cx->ielast = (enum uni_ietype)0;
	cx->repeat.h.present = 0;

	while (uni_msg_len(msg) != 0) {
		if (uni_decode_ie_hdr(&ietype, &hdr, msg, cx, &ielen)) {
			/*
			 * Short header. Set the ielen to an impossible size.
			 * Then we should bump out in the error handling below.
			 * We should have at least an IE type here.
			 */
			ielen = 0xffffffff;
		}
#ifdef DTRACE
		printf("IE %x\n", ietype);
#endif

		if ((iedecl = GET_IEDECL(ietype, hdr.coding)) == NULL ||
		    ietype == UNI_IE_UNREC) {
			/*
			 * entirly unknown IE. Check the length and skip it.
			 * Q.2931 5.6.8.1
			 */
			if (ielen > uni_msg_len(msg))
				msg->b_rptr = msg->b_wptr;
			else
				msg->b_rptr += ielen;
			(void)UNI_SAVE_IERR(cx, ietype, hdr.act, UNI_IERR_UNK);
			err = -1;
			continue;
		}
#ifdef DTRACE
		printf("IE %x known\n", ietype);
#endif
		if (ielen > iedecl->maxlen - 4 || ielen > uni_msg_len(msg)) {
			/*
			 * Information element too long -> content error.
			 * Let the decoding routine set the error flag and
			 * return DEC_ERR.
			 * Q.2931 5.6.8.2
			 */
#if 0
			/*
			 * It is not clear how to best handle this error.
			 */
			if (ielen > iedecl->maxlen - 4)
				ielen = iedecl->maxlen - 4;
#endif

			if (ielen > uni_msg_len(msg))
				ielen = uni_msg_len(msg);

			hdr.present |= UNI_IE_ERROR;

#ifdef DTRACE
			printf("IE %x length too large\n", ietype);
#endif
		}

#ifdef DTRACE
		else
			printf("IE %x length ok\n", ietype);
#endif
		end = msg->b_rptr + ielen;
		ret = uni_msgtable[mtype]->decode(out, msg, ietype,
		    &hdr, ielen, cx);
		msg->b_rptr = end;

#ifdef DTRACE
		printf("IE %x ret %d\n", ietype, ret);
#endif

		switch (ret) {

		  case DEC_OK:	/* ok */
			break;

		  case DEC_ILL:	/* illegal IE */
			/*
			 * Unexpected but recognized.
			 * Q.2931 5.6.8.3
			 */
			(void)UNI_SAVE_IERR(cx, ietype, hdr.act, UNI_IERR_UNK);
			err = -1;
			break;

		  case DEC_ERR:	/* bad IE */
			if (iedecl->flags & UNIFL_ACCESS)
				/* this may be wrong: 5.6.8.2 */
				(void)UNI_SAVE_IERR(cx, ietype, hdr.act, UNI_IERR_ACC);
			else
				(void)UNI_SAVE_IERR(cx, ietype, hdr.act, UNI_IERR_BAD);
			err = -1;
			break;

		  default:
			PANIC(("bad decode return"));
		}
	    	cx->ielast = ietype;
	    	if (ietype != UNI_IE_REPEAT)
			cx->repeat.h.present = 0;
	}
	return err;
}