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
typedef  scalar_t__ vm_paddr_t ;
typedef  int u_int ;
struct dumperinfo {int /*<<< orphan*/  maxiosize; } ;

/* Variables and functions */
 int ECANCELED ; 
 int EINVAL ; 
 size_t MAXDUMPPGS ; 
 int PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 scalar_t__ WDOG_DUMP_INTERVAL ; 
 int /*<<< orphan*/  WD_LASTVAL ; 
 int blk_flush (struct dumperinfo*) ; 
 int cncheckc () ; 
 size_t counter ; 
 int dump_append (struct dumperinfo*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dump_va ; 
 int /*<<< orphan*/  dumpsize ; 
 int fragsz ; 
 int min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pmap_kenter_temporary (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ progress ; 
 int /*<<< orphan*/  report_progress (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdog_kern_pat (int /*<<< orphan*/ ) ; 
 scalar_t__ wdog_next ; 

__attribute__((used)) static int
blk_write(struct dumperinfo *di, char *ptr, vm_paddr_t pa, size_t sz)
{
	size_t len;
	int error, i, c;
	u_int maxdumpsz;

	maxdumpsz = min(di->maxiosize, MAXDUMPPGS * PAGE_SIZE);
	if (maxdumpsz == 0)	/* seatbelt */
		maxdumpsz = PAGE_SIZE;
	error = 0;
	if ((sz % PAGE_SIZE) != 0) {
		printf("size not page aligned\n");
		return (EINVAL);
	}
	if (ptr != NULL && pa != 0) {
		printf("cant have both va and pa!\n");
		return (EINVAL);
	}
	if ((((uintptr_t)pa) % PAGE_SIZE) != 0) {
		printf("address not page aligned %p\n", ptr);
		return (EINVAL);
	}
	if (ptr != NULL) {
		/* If we're doing a virtual dump, flush any pre-existing pa pages */
		error = blk_flush(di);
		if (error)
			return (error);
	}
	while (sz) {
		len = maxdumpsz - fragsz;
		if (len > sz)
			len = sz;
		counter += len;
		progress -= len;
		if (counter >> 24) {
			report_progress(progress, dumpsize);
			counter &= (1<<24) - 1;
		}
		if (progress <= wdog_next) {
			wdog_kern_pat(WD_LASTVAL);
			if (wdog_next > WDOG_DUMP_INTERVAL)
				wdog_next -= WDOG_DUMP_INTERVAL;
			else
				wdog_next = 0;
		}

		if (ptr) {
			error = dump_append(di, ptr, 0, len);
			if (error)
				return (error);
			ptr += len;
			sz -= len;
		} else {
			for (i = 0; i < len; i += PAGE_SIZE)
				dump_va = pmap_kenter_temporary(pa + i, (i + fragsz) >> PAGE_SHIFT);
			fragsz += len;
			pa += len;
			sz -= len;
			if (fragsz == maxdumpsz) {
				error = blk_flush(di);
				if (error)
					return (error);
			}
		}

		/* Check for user abort. */
		c = cncheckc();
		if (c == 0x03)
			return (ECANCELED);
		if (c != -1)
			printf(" (CTRL-C to abort) ");
	}

	return (0);
}