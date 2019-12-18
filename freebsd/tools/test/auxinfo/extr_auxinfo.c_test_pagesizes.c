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
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int getpagesizes (size_t*,int) ; 
 size_t* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
test_pagesizes(void)
{
	size_t *ps;
	int i, nelem;

	nelem = getpagesizes(NULL, 0);
	if (nelem == -1)
		err(1, "getpagesizes(NULL, 0)");
	ps = malloc(nelem * sizeof(size_t));
	if (ps == NULL)
		err(1, "malloc");
	nelem = getpagesizes(ps, nelem);
	if (nelem == -1)
		err(1, "getpagesizes");
	printf("Supported page sizes:");
	for (i = 0; i < nelem; i++)
		printf(" %jd", (intmax_t)ps[i]);
	printf("\n");
}