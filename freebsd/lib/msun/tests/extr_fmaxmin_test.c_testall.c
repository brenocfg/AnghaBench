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
#define  FE_DOWNWARD 131 
#define  FE_TONEAREST 130 
#define  FE_TOWARDZERO 129 
#define  FE_UPWARD 128 
 char* comment ; 
 int /*<<< orphan*/  fesetround (int const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  printf (char*,char*,int,long double,long double,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  testall_r (long double,long double) ; 

__attribute__((used)) static void
testall(int testnum, long double big, long double small)
{
	static const int rmodes[] = {
		FE_TONEAREST, FE_UPWARD, FE_DOWNWARD, FE_TOWARDZERO
	};
	int i;

	for (i = 0; i < 4; i++) {
		fesetround(rmodes[i]);
		if (!testall_r(big, small)) {
			fprintf(stderr, "FAILURE in rounding mode %d\n",
				rmodes[i]);
			break;
		}
	}
	printf("%sok %d - big = %.20Lg, small = %.20Lg%s\n",
	       (i == 4) ? "" : "not ", testnum, big, small,
	       comment == NULL ? "" : comment);
}