#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  machine; int /*<<< orphan*/  port; } ;
struct TYPE_6__ {int /*<<< orphan*/  am_failure; int /*<<< orphan*/  am_success; } ;
struct TYPE_9__ {TYPE_3__ ar_arg_termid; TYPE_1__ ar_arg_amask; int /*<<< orphan*/  ar_arg_asid; int /*<<< orphan*/  ar_arg_auid; } ;
struct kaudit_record {TYPE_4__ k_ar; } ;
struct TYPE_10__ {int /*<<< orphan*/  machine; int /*<<< orphan*/  port; } ;
struct TYPE_7__ {int /*<<< orphan*/  am_failure; int /*<<< orphan*/  am_success; } ;
struct auditinfo {TYPE_5__ ai_termid; TYPE_2__ ai_mask; int /*<<< orphan*/  ai_asid; int /*<<< orphan*/  ai_auid; } ;

/* Variables and functions */
 int ARG_AMASK ; 
 int ARG_ASID ; 
 int ARG_AUID ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int) ; 
 int ARG_TERMID ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_auditinfo(struct auditinfo *au_info)
{
	struct kaudit_record *ar;

	ar = currecord();
	if (ar == NULL)
		return;

	ar->k_ar.ar_arg_auid = au_info->ai_auid;
	ar->k_ar.ar_arg_asid = au_info->ai_asid;
	ar->k_ar.ar_arg_amask.am_success = au_info->ai_mask.am_success;
	ar->k_ar.ar_arg_amask.am_failure = au_info->ai_mask.am_failure;
	ar->k_ar.ar_arg_termid.port = au_info->ai_termid.port;
	ar->k_ar.ar_arg_termid.machine = au_info->ai_termid.machine;
	ARG_SET_VALID(ar, ARG_AUID | ARG_ASID | ARG_AMASK | ARG_TERMID);
}