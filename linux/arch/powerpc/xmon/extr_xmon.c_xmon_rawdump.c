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

/* Variables and functions */
 char** fault_chars ; 
 size_t fault_type ; 
 long mread (unsigned long,unsigned char*,long) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void xmon_rawdump (unsigned long adrs, long ndump)
{
	long n, m, r, nr;
	unsigned char temp[16];

	for (n = ndump; n > 0;) {
		r = n < 16? n: 16;
		nr = mread(adrs, temp, r);
		adrs += nr;
		for (m = 0; m < r; ++m) {
			if (m < nr)
				printf("%.2x", temp[m]);
			else
				printf("%s", fault_chars[fault_type]);
		}
		n -= r;
		if (nr < r)
			break;
	}
	printf("\n");
}