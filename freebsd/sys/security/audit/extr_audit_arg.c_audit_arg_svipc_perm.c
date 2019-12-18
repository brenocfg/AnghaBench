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
struct TYPE_2__ {int /*<<< orphan*/  ar_arg_svipc_perm; } ;
struct kaudit_record {TYPE_1__ k_ar; } ;
struct ipc_perm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARG_SVIPC_PERM ; 
 int /*<<< orphan*/  bcopy (struct ipc_perm*,int /*<<< orphan*/ *,int) ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_svipc_perm(struct ipc_perm *perm)
{
	struct kaudit_record *ar;

	ar = currecord();
	if (ar == NULL)
		return;

	bcopy(perm, &ar->k_ar.ar_arg_svipc_perm,
	    sizeof(ar->k_ar.ar_arg_svipc_perm));
	ARG_SET_VALID(ar, ARG_SVIPC_PERM);
}