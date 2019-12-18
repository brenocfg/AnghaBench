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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 scalar_t__ isset (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
pblklist(void *vp, int max, off_t offset, int fflag)
{
	int i, j;
	char *p;

	for (i = 0, p = vp; i < max; i++) {
		if (isset(p, i)) {
			printf("%jd", (intmax_t)(i + offset));
			if (fflag < 2) {
				j = i;
				while ((i+1)<max && isset(p, i+1))
					i++;
				if (i != j)
					printf("-%jd", (intmax_t)(i + offset));
			}
			printf("\n");
		}
	}
}