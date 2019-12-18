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
struct gkc_summary {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (double*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,long) ; 
 struct gkc_summary* gkc_combine (struct gkc_summary*,struct gkc_summary*) ; 
 int /*<<< orphan*/  gkc_insert_value (struct gkc_summary*,int) ; 
 int /*<<< orphan*/  gkc_print_summary (struct gkc_summary*) ; 
 int /*<<< orphan*/  gkc_sanity_check (struct gkc_summary*) ; 
 struct gkc_summary* gkc_summary_alloc (double) ; 
 int /*<<< orphan*/  gkc_summary_free (struct gkc_summary*) ; 
 int /*<<< orphan*/  print_query (struct gkc_summary*,double) ; 
 int random () ; 
 int /*<<< orphan*/  srandom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ tofile ; 

int main(void)
{
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
	unsigned int i;
#if 0
	double input[] = {
		3658, 3673, 3693, 3715, 3723, 3724, 3724, 3690, 3695, 3689, 3695, 3700,
		3690, 3699, 3699, 3701, 3704, 3704, 3714, 3707, 3698, 3701, 3697, 3697,
		3712, 3713, 3714, 3715, 3717, 3712, 3712, 3717, 3728, 3728, 3744, 3751,
		3764, 3751, 3798, 3802, 3800, 3824, 3810, 3824, 3811, 3802, 3811, 3801,
		3791, 3796, 3803, 3817, 3819, 3818, 3815, 3804, 3796, 3784, 3783, 3784,
		3774, 3776, 3776, 3764, 3763, 3806, 3819, 3835, 3825, 3786, 3795, 3795,
		3776, 3760, 3789, 3786, 3771, 3778, 3782, 3776, 3781, 3784, 3801, 3810,
		3815, 3792, 3764, 3770, 3746, 3741, 3746, 3756, 3755, 3775, 3776, 3773,
		3777, 3801, 3804, 3807
	};
#else
	double input[] = { 12, 6, 10, 1 };
#endif
	FILE *out;
	struct gkc_summary *summary;
	struct gkc_summary *s1, *s2, *snew;

	summary = gkc_summary_alloc(0.01);
	print_query(summary, 0.1);
	goto test_combine;
	summary = gkc_summary_alloc(0.01);

#if 0
	for (i = 0; i < ARRAY_SIZE(input); i++) {
		gkc_insert_value(&summary, input[i]);
	}
	gkc_print_summary(&summary);
	print_query(&summary, 0);
	print_query(&summary, .25);
	print_query(&summary, .5);
	print_query(&summary, .75);
	print_query(&summary, 1);
	return 0;
#else
	(void)input;
#endif

#define tofile 0
	if (tofile) {
		out = fopen("data", "w+");
	}
	srandom(time(NULL));
	for (i = 0; i < 10 * 1000 * 1000; i++) {
		long r = random() % 10000;
		gkc_insert_value(summary, r);
		if (tofile) {
			fprintf(out, "%ld\n", r);
		}
	}
	if (tofile) {
		fclose(out);
	}
	gkc_print_summary(summary);
	print_query(summary, .02);
	print_query(summary, .1);
	print_query(summary, .25);
	print_query(summary, .5);
	print_query(summary, .75);
	print_query(summary, .82);
	print_query(summary, .88);
	print_query(summary, .86);
	print_query(summary, .99);

	gkc_sanity_check(summary);

	gkc_summary_free(summary);

test_combine:
	s1 = gkc_summary_alloc(0.01);
	s2 = gkc_summary_alloc(0.01);

	for (i = 0; i < 1 * 10 * 1000; i++) {
		long r = random() % 10000;
		gkc_insert_value(s1, r);
	}
#if 0
	for (i = 0; i < 1 * 1 * 1000; i++) {
		gkc_insert_value(s2, 111);
	}
#endif
	snew = gkc_combine(s1, s2);
	gkc_summary_free(s1);
	gkc_summary_free(s2);

	gkc_print_summary(snew);
	print_query(snew, .02);
	print_query(snew, .1);
	print_query(snew, .25);
	print_query(snew, .5);
	print_query(snew, .75);
	print_query(snew, .82);
	print_query(snew, .88);
	print_query(snew, .86);
	print_query(snew, .99);

	gkc_sanity_check(snew);

	gkc_summary_free(snew);

	return 0;
}