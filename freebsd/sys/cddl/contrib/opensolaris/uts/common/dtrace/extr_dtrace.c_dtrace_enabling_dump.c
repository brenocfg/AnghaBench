#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* dtpd_provider; char* dtpd_mod; char* dtpd_func; char* dtpd_name; } ;
typedef  TYPE_2__ dtrace_probedesc_t ;
struct TYPE_7__ {int dten_ndesc; TYPE_1__** dten_desc; } ;
typedef  TYPE_3__ dtrace_enabling_t ;
struct TYPE_5__ {TYPE_2__ dted_probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_NOTE ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*,char*,char*) ; 

__attribute__((used)) static void
dtrace_enabling_dump(dtrace_enabling_t *enab)
{
	int i;

	for (i = 0; i < enab->dten_ndesc; i++) {
		dtrace_probedesc_t *desc = &enab->dten_desc[i]->dted_probe;

#ifdef __FreeBSD__
		printf("dtrace: enabling probe %d (%s:%s:%s:%s)\n", i,
		    desc->dtpd_provider, desc->dtpd_mod,
		    desc->dtpd_func, desc->dtpd_name);
#else
		cmn_err(CE_NOTE, "enabling probe %d (%s:%s:%s:%s)", i,
		    desc->dtpd_provider, desc->dtpd_mod,
		    desc->dtpd_func, desc->dtpd_name);
#endif
	}
}