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
struct send_pack_args {int /*<<< orphan*/  send_mirror; } ;
struct ref {int status; int /*<<< orphan*/  peer_ref; } ;

/* Variables and functions */
 int CHECK_REF_NO_PUSH ; 
 int CHECK_REF_STATUS_REJECTED ; 
 int CHECK_REF_UPTODATE ; 
#define  REF_STATUS_REJECT_ALREADY_EXISTS 134 
#define  REF_STATUS_REJECT_FETCH_FIRST 133 
#define  REF_STATUS_REJECT_NEEDS_FORCE 132 
#define  REF_STATUS_REJECT_NODELETE 131 
#define  REF_STATUS_REJECT_NONFASTFORWARD 130 
#define  REF_STATUS_REJECT_STALE 129 
#define  REF_STATUS_UPTODATE 128 

__attribute__((used)) static int check_to_send_update(const struct ref *ref, const struct send_pack_args *args)
{
	if (!ref->peer_ref && !args->send_mirror)
		return CHECK_REF_NO_PUSH;

	/* Check for statuses set by set_ref_status_for_push() */
	switch (ref->status) {
	case REF_STATUS_REJECT_NONFASTFORWARD:
	case REF_STATUS_REJECT_ALREADY_EXISTS:
	case REF_STATUS_REJECT_FETCH_FIRST:
	case REF_STATUS_REJECT_NEEDS_FORCE:
	case REF_STATUS_REJECT_STALE:
	case REF_STATUS_REJECT_NODELETE:
		return CHECK_REF_STATUS_REJECTED;
	case REF_STATUS_UPTODATE:
		return CHECK_REF_UPTODATE;
	default:
		return 0;
	}
}