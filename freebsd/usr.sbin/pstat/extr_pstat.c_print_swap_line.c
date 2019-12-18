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
typedef  int /*<<< orphan*/  usedbuf ;
typedef  char* intmax_t ;
typedef  int /*<<< orphan*/  availbuf ;

/* Variables and functions */
 scalar_t__ CONVERT (char*) ; 
 int /*<<< orphan*/  CONVERT_BLOCKS (char*) ; 
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int HN_B ; 
 int HN_DECIMAL ; 
 int HN_NOSPACE ; 
 int /*<<< orphan*/  getbsize (int*,long*) ; 
 int getpagesize () ; 
 scalar_t__ humanflag ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 

__attribute__((used)) static void
print_swap_line(const char *swdevname, intmax_t nblks, intmax_t bused,
    intmax_t bavail, float bpercent)
{
	char usedbuf[5];
	char availbuf[5];
	int hlen, pagesize;
	long blocksize;

	pagesize = getpagesize();
	getbsize(&hlen, &blocksize);

	printf("%-15s %*jd ", swdevname, hlen, CONVERT(nblks));
	if (humanflag) {
		humanize_number(usedbuf, sizeof(usedbuf),
		    CONVERT_BLOCKS(bused), "",
		    HN_AUTOSCALE, HN_B | HN_NOSPACE | HN_DECIMAL);
		humanize_number(availbuf, sizeof(availbuf),
		    CONVERT_BLOCKS(bavail), "",
		    HN_AUTOSCALE, HN_B | HN_NOSPACE | HN_DECIMAL);
		printf("%8s %8s %5.0f%%\n", usedbuf, availbuf, bpercent);
	} else {
		printf("%8jd %8jd %5.0f%%\n", (intmax_t)CONVERT(bused),
		    (intmax_t)CONVERT(bavail), bpercent);
	}
}