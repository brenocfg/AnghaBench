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
struct TYPE_2__ {int ar_arg_argc; int /*<<< orphan*/  ar_arg_argv; } ;
struct kaudit_record {TYPE_1__ k_ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_ARGV ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_AUDITTEXT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ audit_argv ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,int) ; 
 struct kaudit_record* currecord () ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
audit_arg_argv(char *argv, int argc, int length)
{
	struct kaudit_record *ar;

	if (audit_argv == 0)
		return;

	ar = currecord();
	if (ar == NULL)
		return;

	ar->k_ar.ar_arg_argv = malloc(length, M_AUDITTEXT, M_WAITOK);
	bcopy(argv, ar->k_ar.ar_arg_argv, length);
	ar->k_ar.ar_arg_argc = argc;
	ARG_SET_VALID(ar, ARG_ARGV);
}