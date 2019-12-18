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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int DBL_MANT_DIG ; 
 int DBL_MAX_EXP ; 
 int DBL_MIN_EXP ; 
 int FLT_MANT_DIG ; 
 int FLT_MAX_EXP ; 
 int FLT_MIN_EXP ; 
 int FP_ILOGB0 ; 
 int FP_ILOGBNAN ; 
 long double INFINITY ; 
 int INT_MAX ; 
 int LDBL_MANT_DIG ; 
 int LDBL_MAX_EXP ; 
 int LDBL_MIN_EXP ; 
 long double NAN ; 
 int /*<<< orphan*/  assert (int) ; 
 int ilogb (double) ; 
 int ilogbf (float) ; 
 int ilogbl (long double) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 double strtod (char*,char**) ; 
 float strtof (char*,char**) ; 
 long double strtold (char*,char**) ; 

int
main(void)
{
	char buf[128], *end;
	double d;
	float f;
	long double ld;
	int e, i;

	printf("1..3\n");
	assert(ilogb(0) == FP_ILOGB0);
	assert(ilogb(NAN) == FP_ILOGBNAN);
	assert(ilogb(INFINITY) == INT_MAX);
	for (e = DBL_MIN_EXP - DBL_MANT_DIG; e < DBL_MAX_EXP; e++) {
		snprintf(buf, sizeof(buf), "0x1.p%d", e);
		d = strtod(buf, &end);
		assert(*end == '\0');
		i = ilogb(d);
		assert(i == e);
	}
	printf("ok 1 - ilogb\n");

	assert(ilogbf(0) == FP_ILOGB0);
	assert(ilogbf(NAN) == FP_ILOGBNAN);
	assert(ilogbf(INFINITY) == INT_MAX);
	for (e = FLT_MIN_EXP - FLT_MANT_DIG; e < FLT_MAX_EXP; e++) {
		snprintf(buf, sizeof(buf), "0x1.p%d", e);
		f = strtof(buf, &end);
		assert(*end == '\0');
		i = ilogbf(f);
		assert(i == e);
	}
	printf("ok 2 - ilogbf\n");

	assert(ilogbl(0) == FP_ILOGB0);
	assert(ilogbl(NAN) == FP_ILOGBNAN);
	assert(ilogbl(INFINITY) == INT_MAX);
	for (e = LDBL_MIN_EXP - LDBL_MANT_DIG; e < LDBL_MAX_EXP; e++) {
		snprintf(buf, sizeof(buf), "0x1.p%d", e);
		ld = strtold(buf, &end);
		assert(*end == '\0');
		i = ilogbl(ld);
		assert(i == e);
	}
	printf("ok 3 - ilogbl\n");

	return (0);
}