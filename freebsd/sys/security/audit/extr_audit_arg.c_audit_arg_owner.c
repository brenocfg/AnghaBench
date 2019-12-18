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
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_2__ {int /*<<< orphan*/  ar_arg_gid; int /*<<< orphan*/  ar_arg_uid; } ;
struct kaudit_record {TYPE_1__ k_ar; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int ARG_GID ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int) ; 
 int ARG_UID ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_owner(uid_t uid, gid_t gid)
{
	struct kaudit_record *ar;

	ar = currecord();
	if (ar == NULL)
		return;

	ar->k_ar.ar_arg_uid = uid;
	ar->k_ar.ar_arg_gid = gid;
	ARG_SET_VALID(ar, ARG_UID | ARG_GID);
}