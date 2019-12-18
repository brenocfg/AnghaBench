#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct sysinit {int subsystem; scalar_t__ order; scalar_t__ udata; int /*<<< orphan*/  (* func ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DB_STGY_ANY ; 
 int /*<<< orphan*/  DB_STGY_PROC ; 
 int /*<<< orphan*/  Giant ; 
 int MA_NOTRECURSED ; 
 int MA_OWNED ; 
 int /*<<< orphan*/  M_TEMP ; 
 int RB_VERBOSE ; 
 struct sysinit** SET_BEGIN (int /*<<< orphan*/ ) ; 
 struct sysinit** SET_LIMIT (int /*<<< orphan*/ ) ; 
 int SI_SUB_COPYRIGHT ; 
 int SI_SUB_DONE ; 
 int SI_SUB_DUMMY ; 
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 int boothowto ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  free (struct sysinit**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 struct sysinit** newsysinit ; 
 struct sysinit** newsysinit_end ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  swapper () ; 
 char* symbol_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sysinit** sysinit ; 
 struct sysinit** sysinit_end ; 
 int /*<<< orphan*/  sysinit_set ; 
 scalar_t__ verbose_sysinit ; 

void
mi_startup(void)
{

	struct sysinit **sipp;	/* system initialization*/
	struct sysinit **xipp;	/* interior loop of sort*/
	struct sysinit *save;	/* bubble*/

#if defined(VERBOSE_SYSINIT)
	int last;
	int verbose;
#endif

	TSENTER();

	if (boothowto & RB_VERBOSE)
		bootverbose++;

	if (sysinit == NULL) {
		sysinit = SET_BEGIN(sysinit_set);
		sysinit_end = SET_LIMIT(sysinit_set);
	}

restart:
	/*
	 * Perform a bubble sort of the system initialization objects by
	 * their subsystem (primary key) and order (secondary key).
	 */
	for (sipp = sysinit; sipp < sysinit_end; sipp++) {
		for (xipp = sipp + 1; xipp < sysinit_end; xipp++) {
			if ((*sipp)->subsystem < (*xipp)->subsystem ||
			     ((*sipp)->subsystem == (*xipp)->subsystem &&
			      (*sipp)->order <= (*xipp)->order))
				continue;	/* skip*/
			save = *sipp;
			*sipp = *xipp;
			*xipp = save;
		}
	}

#if defined(VERBOSE_SYSINIT)
	last = SI_SUB_COPYRIGHT;
	verbose = 0;
#if !defined(DDB)
	printf("VERBOSE_SYSINIT: DDB not enabled, symbol lookups disabled.\n");
#endif
#endif

	/*
	 * Traverse the (now) ordered list of system initialization tasks.
	 * Perform each task, and continue on to the next task.
	 */
	for (sipp = sysinit; sipp < sysinit_end; sipp++) {

		if ((*sipp)->subsystem == SI_SUB_DUMMY)
			continue;	/* skip dummy task(s)*/

		if ((*sipp)->subsystem == SI_SUB_DONE)
			continue;

#if defined(VERBOSE_SYSINIT)
		if ((*sipp)->subsystem > last && verbose_sysinit != 0) {
			verbose = 1;
			last = (*sipp)->subsystem;
			printf("subsystem %x\n", last);
		}
		if (verbose) {
#if defined(DDB)
			const char *func, *data;

			func = symbol_name((vm_offset_t)(*sipp)->func,
			    DB_STGY_PROC);
			data = symbol_name((vm_offset_t)(*sipp)->udata,
			    DB_STGY_ANY);
			if (func != NULL && data != NULL)
				printf("   %s(&%s)... ", func, data);
			else if (func != NULL)
				printf("   %s(%p)... ", func, (*sipp)->udata);
			else
#endif
				printf("   %p(%p)... ", (*sipp)->func,
				    (*sipp)->udata);
		}
#endif

		/* Call function */
		(*((*sipp)->func))((*sipp)->udata);

#if defined(VERBOSE_SYSINIT)
		if (verbose)
			printf("done.\n");
#endif

		/* Check off the one we're just done */
		(*sipp)->subsystem = SI_SUB_DONE;

		/* Check if we've installed more sysinit items via KLD */
		if (newsysinit != NULL) {
			if (sysinit != SET_BEGIN(sysinit_set))
				free(sysinit, M_TEMP);
			sysinit = newsysinit;
			sysinit_end = newsysinit_end;
			newsysinit = NULL;
			newsysinit_end = NULL;
			goto restart;
		}
	}

	TSEXIT();	/* Here so we don't overlap with start_init. */

	mtx_assert(&Giant, MA_OWNED | MA_NOTRECURSED);
	mtx_unlock(&Giant);

	/*
	 * Now hand over this thread to swapper.
	 */
	swapper();
	/* NOTREACHED*/
}