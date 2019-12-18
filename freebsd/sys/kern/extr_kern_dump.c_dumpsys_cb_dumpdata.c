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
typedef  size_t vm_paddr_t ;
typedef  char* uintmax_t ;
typedef  size_t uint64_t ;
typedef  size_t u_int ;
struct dumperinfo {size_t maxiosize; } ;
struct dump_pa {size_t pa_size; size_t pa_start; } ;

/* Variables and functions */
 int ECANCELED ; 
 int /*<<< orphan*/  MAXDUMPPGS ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 scalar_t__ PG2MB (size_t) ; 
 int /*<<< orphan*/  WD_LASTVAL ; 
 int cncheckc () ; 
 int dump_append (struct dumperinfo*,void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dumpsys_map_chunk (size_t,size_t,void**) ; 
 int /*<<< orphan*/  dumpsys_unmap_chunk (size_t,size_t,void*) ; 
 int /*<<< orphan*/  dumpsys_wbinv_all () ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  wdog_kern_pat (int /*<<< orphan*/ ) ; 

int
dumpsys_cb_dumpdata(struct dump_pa *mdp, int seqnr, void *arg)
{
	struct dumperinfo *di = (struct dumperinfo*)arg;
	vm_paddr_t pa;
	void *va;
	uint64_t pgs;
	size_t counter, sz, chunk;
	int c, error;
	u_int maxdumppgs;

	error = 0;	/* catch case in which chunk size is 0 */
	counter = 0;	/* Update twiddle every 16MB */
	va = NULL;
	pgs = mdp->pa_size / PAGE_SIZE;
	pa = mdp->pa_start;
	maxdumppgs = min(di->maxiosize / PAGE_SIZE, MAXDUMPPGS);
	if (maxdumppgs == 0)	/* seatbelt */
		maxdumppgs = 1;

	printf("  chunk %d: %juMB (%ju pages)", seqnr, (uintmax_t)PG2MB(pgs),
	    (uintmax_t)pgs);

	dumpsys_wbinv_all();
	while (pgs) {
		chunk = pgs;
		if (chunk > maxdumppgs)
			chunk = maxdumppgs;
		sz = chunk << PAGE_SHIFT;
		counter += sz;
		if (counter >> 24) {
			printf(" %ju", (uintmax_t)PG2MB(pgs));
			counter &= (1 << 24) - 1;
		}

		dumpsys_map_chunk(pa, chunk, &va);
		wdog_kern_pat(WD_LASTVAL);

		error = dump_append(di, va, 0, sz);
		dumpsys_unmap_chunk(pa, chunk, va);
		if (error)
			break;
		pgs -= chunk;
		pa += sz;

		/* Check for user abort. */
		c = cncheckc();
		if (c == 0x03)
			return (ECANCELED);
		if (c != -1)
			printf(" (CTRL-C to abort) ");
	}
	printf(" ... %s\n", (error) ? "fail" : "ok");
	return (error);
}