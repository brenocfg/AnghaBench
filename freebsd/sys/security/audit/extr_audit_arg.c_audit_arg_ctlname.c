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
struct TYPE_2__ {int ar_arg_len; int /*<<< orphan*/  ar_arg_ctlname; } ;
struct kaudit_record {TYPE_1__ k_ar; } ;

/* Variables and functions */
 int ARG_CTLNAME ; 
 int ARG_LEN ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int) ; 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ *,int) ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_ctlname(int *name, int namelen)
{
	struct kaudit_record *ar;

	ar = currecord();
	if (ar == NULL)
		return;

	bcopy(name, &ar->k_ar.ar_arg_ctlname, namelen * sizeof(int));
	ar->k_ar.ar_arg_len = namelen;
	ARG_SET_VALID(ar, ARG_CTLNAME | ARG_LEN);
}