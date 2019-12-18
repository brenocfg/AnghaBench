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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
memdiffs(unsigned char *p1, unsigned char *p2, unsigned nb, unsigned maxpr)
{
	unsigned n, prt;

	prt = 0;
	for( n = nb; n > 0; --n )
		if( *p1++ != *p2++ )
			if( ++prt <= maxpr )
				printf("%px %.2x # %px %.2x\n", p1 - 1,
					p1[-1], p2 - 1, p2[-1]);
	if( prt > maxpr )
		printf("Total of %d differences\n", prt);
}