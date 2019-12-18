#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct evname_elem {int /*<<< orphan*/  ene_bsm_probe_id; } ;
typedef  int /*<<< orphan*/  dtrace_id_t ;
struct TYPE_3__ {int dtargd_ndx; int /*<<< orphan*/  dtargd_native; } ;
typedef  TYPE_1__ dtrace_argdesc_t ;

/* Variables and functions */
 void* DTRACE_ARGNONE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
dtaudit_getargdesc(void *arg, dtrace_id_t id, void *parg,
    dtrace_argdesc_t *desc)
{
	struct evname_elem *ene;
	const char *p;

	ene = (struct evname_elem *)parg;
	p = NULL;
	switch (desc->dtargd_ndx) {
	case 0:
		/* Audit event name. */
		p = "char *";
		break;

	case 1:
		/* In-kernel audit record. */
		p = "struct audit_record *";
		break;

	case 2:
		/* BSM data, if present. */
		if (id == ene->ene_bsm_probe_id)
			p = "const void *";
		else
			desc->dtargd_ndx = DTRACE_ARGNONE;
		break;

	case 3:
		/* BSM length, if present. */
		if (id == ene->ene_bsm_probe_id)
			p = "size_t";
		else
			desc->dtargd_ndx = DTRACE_ARGNONE;
		break;

	default:
		desc->dtargd_ndx = DTRACE_ARGNONE;
		break;
	}
	if (p != NULL)
		strlcpy(desc->dtargd_native, p, sizeof(desc->dtargd_native));
}