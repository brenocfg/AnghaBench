#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct PROCENTRY {int dummy; } ;
struct IOAPICENTRY {int dummy; } ;
struct INTENTRY {int dummy; } ;
struct BUSENTRY {int dummy; } ;
typedef  TYPE_1__* proc_entry_ptr ;
typedef  TYPE_2__* mpfps_t ;
typedef  TYPE_2__* mpcth_t ;
struct TYPE_8__ {scalar_t__ config_type; int entry_count; int /*<<< orphan*/  pap; } ;
struct TYPE_7__ {int cpu_flags; int /*<<< orphan*/  apic_id; } ;

/* Variables and functions */
 int PROCENTRY_FLAG_EN ; 
 int /*<<< orphan*/  PTOV (int /*<<< orphan*/ ) ; 
 TYPE_2__* biosmptable_check_mpcth (int /*<<< orphan*/ ) ; 
 TYPE_2__* biosmptable_find_mpfps () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memclose () ; 
 int /*<<< orphan*/  memopen () ; 
 int /*<<< orphan*/  warnx (char*,char,...) ; 

int
biosmptable_detect(void)
{
    mpfps_t mpfps;
    mpcth_t mpcth;
    char *entry_type_p;
    proc_entry_ptr proc;
    int ncpu, i;

    if (!memopen())
	return -1;		/* XXX 0? */
    /* locate and validate the mpfps */
    mpfps = biosmptable_find_mpfps();
    mpcth = NULL;
    if (mpfps == NULL) {
	ncpu = 0;
    } else if (mpfps->config_type != 0) {
	/* 
	 * If thie config_type is nonzero then this is a default configuration
	 * from Chapter 5 in the MP spec.  Report 2 cpus and 1 I/O APIC.
	 */
    	ncpu = 2;
    } else {
	ncpu = 0;
	mpcth = biosmptable_check_mpcth(PTOV(mpfps->pap));
	if (mpcth != NULL) {
	    entry_type_p = (char *)(mpcth + 1);
	    for (i = 0; i < mpcth->entry_count; i++) {
		switch (*entry_type_p) {
		case 0:
		    entry_type_p += sizeof(struct PROCENTRY);
		    proc = (proc_entry_ptr) entry_type_p;
		    warnx("MPTable: Found CPU APIC ID %d %s",
			proc->apic_id,
			proc->cpu_flags & PROCENTRY_FLAG_EN ?
				"enabled" : "disabled");
		    if (proc->cpu_flags & PROCENTRY_FLAG_EN)
			ncpu++;
		    break;
		case 1:
		    entry_type_p += sizeof(struct BUSENTRY);
		    break;
		case 2:
		    entry_type_p += sizeof(struct IOAPICENTRY);
		    break;
		case 3:
		case 4:
		    entry_type_p += sizeof(struct INTENTRY);
		    break;
		default:
		    warnx("unknown mptable entry type (%d)", *entry_type_p);
		    goto done;		/* XXX error return? */
		}
	    }
	done:
	    ;
	}
    }
    memclose();
    if (mpcth != NULL)
	free(mpcth);
    if (mpfps != NULL)
	free(mpfps);

    return ncpu;
}