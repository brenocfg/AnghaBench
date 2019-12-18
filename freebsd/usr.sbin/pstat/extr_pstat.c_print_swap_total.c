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
struct TYPE_2__ {double ksw_used; double ksw_total; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT (double) ; 
 int /*<<< orphan*/  getbsize (int*,long*) ; 
 int getpagesize () ; 
 int nswdev ; 
 int /*<<< orphan*/  print_swap_line (char*,double,double,double,double) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ swtot ; 
 scalar_t__ totalflag ; 

__attribute__((used)) static void
print_swap_total(void)
{
	int hlen, pagesize;
	long blocksize;

	pagesize = getpagesize();
	getbsize(&hlen, &blocksize);
	if (totalflag) {
		blocksize = 1024 * 1024;
		(void)printf("%jdM/%jdM swap space\n",
		    CONVERT(swtot.ksw_used), CONVERT(swtot.ksw_total));
	} else if (nswdev > 1) {
		print_swap_line("Total", swtot.ksw_total, swtot.ksw_used,
		    swtot.ksw_total - swtot.ksw_used,
		    (swtot.ksw_used * 100.0) / swtot.ksw_total);
	}
}