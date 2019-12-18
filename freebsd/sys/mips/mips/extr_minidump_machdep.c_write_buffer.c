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
typedef  scalar_t__ u_int ;
struct dumperinfo {scalar_t__ maxiosize; } ;

/* Variables and functions */
 int ECANCELED ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WD_LASTVAL ; 
 int cncheckc () ; 
 size_t counter ; 
 int dump_append (struct dumperinfo*,char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dumpsize ; 
 size_t min (scalar_t__,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t progress ; 
 int /*<<< orphan*/  report_progress (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdog_kern_pat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
write_buffer(struct dumperinfo *di, char *ptr, size_t sz)
{
	size_t len;
	int error, c;
	u_int maxdumpsz;

	maxdumpsz = di->maxiosize;

	if (maxdumpsz == 0)	/* seatbelt */
		maxdumpsz = PAGE_SIZE;

	error = 0;

	while (sz) {
		len = min(maxdumpsz, sz);
		counter += len;
		progress -= len;

		if (counter >> 22) {
			report_progress(progress, dumpsize);
			counter &= (1<<22) - 1;
		}

		wdog_kern_pat(WD_LASTVAL);

		if (ptr) {
			error = dump_append(di, ptr, 0, len);
			if (error)
				return (error);
			ptr += len;
			sz -= len;
		} else {
			panic("pa is not supported");
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