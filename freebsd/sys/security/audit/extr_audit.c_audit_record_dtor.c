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
struct TYPE_3__ {int /*<<< orphan*/ * gidset; } ;
struct TYPE_4__ {TYPE_1__ ar_arg_groups; int /*<<< orphan*/ * ar_arg_envv; int /*<<< orphan*/ * ar_arg_argv; int /*<<< orphan*/ * ar_arg_text; int /*<<< orphan*/ * ar_arg_upath2; int /*<<< orphan*/ * ar_arg_upath1; } ;
struct kaudit_record {TYPE_2__ k_ar; int /*<<< orphan*/ * k_udata; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_AUDITDATA ; 
 int /*<<< orphan*/  M_AUDITGIDSET ; 
 int /*<<< orphan*/  M_AUDITPATH ; 
 int /*<<< orphan*/  M_AUDITTEXT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
audit_record_dtor(void *mem, int size, void *arg)
{
	struct kaudit_record *ar;

	KASSERT(sizeof(*ar) == size, ("audit_record_dtor: wrong size"));

	ar = mem;
	if (ar->k_ar.ar_arg_upath1 != NULL)
		free(ar->k_ar.ar_arg_upath1, M_AUDITPATH);
	if (ar->k_ar.ar_arg_upath2 != NULL)
		free(ar->k_ar.ar_arg_upath2, M_AUDITPATH);
	if (ar->k_ar.ar_arg_text != NULL)
		free(ar->k_ar.ar_arg_text, M_AUDITTEXT);
	if (ar->k_udata != NULL)
		free(ar->k_udata, M_AUDITDATA);
	if (ar->k_ar.ar_arg_argv != NULL)
		free(ar->k_ar.ar_arg_argv, M_AUDITTEXT);
	if (ar->k_ar.ar_arg_envv != NULL)
		free(ar->k_ar.ar_arg_envv, M_AUDITTEXT);
	if (ar->k_ar.ar_arg_groups.gidset != NULL)
		free(ar->k_ar.ar_arg_groups.gidset, M_AUDITGIDSET);
}