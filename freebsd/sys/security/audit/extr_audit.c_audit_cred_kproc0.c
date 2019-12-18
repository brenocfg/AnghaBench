#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  at_type; } ;
struct TYPE_4__ {TYPE_1__ ai_termid; int /*<<< orphan*/  ai_auid; } ;
struct ucred {TYPE_2__ cr_audit; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU_DEFAUDITID ; 
 int /*<<< orphan*/  AU_IPv4 ; 

void
audit_cred_kproc0(struct ucred *cred)
{

	cred->cr_audit.ai_auid = AU_DEFAUDITID;
	cred->cr_audit.ai_termid.at_type = AU_IPv4;
}