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
typedef  int /*<<< orphan*/  bitstr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  bit_ffc (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  bit_ffs (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char,...) ; 

__attribute__((used)) static void
printbits(FILE *file, bitstr_t *b, int n)
{
	int i;
	int jc, js;

	bit_ffc(b, n, &jc);
	bit_ffs(b, n, &js);

	(void) fprintf(file, "%3d %3d ", jc, js);

	for (i=0; i < n; i++) {
		(void) fprintf(file, "%c", (bit_test(b, i) ? '1' : '0'));
	}

	(void) fprintf(file, "%c", '\n');
}