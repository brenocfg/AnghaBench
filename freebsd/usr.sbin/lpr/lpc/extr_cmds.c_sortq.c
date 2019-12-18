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
struct dirent {char* d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_TO_CAT (char const*,int,char const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int
sortq(const struct dirent **a, const struct dirent **b)
{
	const int a_lt_b = -1, a_gt_b = 1, cat_other = 10;
	const char *fname_a, *fname_b, *jnum_a, *jnum_b;
	int cat_a, cat_b, ch, res, seq_a, seq_b;

	fname_a = (*a)->d_name;
	fname_b = (*b)->d_name;

	/*
	 * First separate filenames into categories.  Categories are
	 * legitimate `cf', `df', `rf' & `tf' filenames, and "other" - in
	 * that order.  It is critical that the mapping be exactly the
	 * same for 'a' vs 'b', so define a macro for the job.
	 *
	 * [aside: the standard `cf' file has the jobnumber start in
	 * position 4, but some implementations have that as an extra
	 * file-sequence letter, and start the job number in position 5.]
	 */
#define MAP_TO_CAT(fname_X,cat_X,jnum_X,seq_X) do { \
	cat_X = cat_other;    \
	ch = *(fname_X + 2);  \
	jnum_X = fname_X + 3; \
	seq_X = 0;            \
	if ((*(fname_X + 1) == 'f') && (isalpha(ch))) { \
		seq_X = ch; \
		if (*fname_X == 'c') \
			cat_X = 1; \
		else if (*fname_X == 'd') \
			cat_X = 2; \
		else if (*fname_X == 'r') \
			cat_X = 3; \
		else if (*fname_X == 't') \
			cat_X = 4; \
		if (cat_X != cat_other) { \
			ch = *jnum_X; \
			if (!isdigit(ch)) { \
				if (isalpha(ch)) { \
					jnum_X++; \
					ch = *jnum_X; \
					seq_X = (seq_X << 8) + ch; \
				} \
				if (!isdigit(ch)) \
					cat_X = cat_other; \
			} \
		} \
	} \
} while (0)

	MAP_TO_CAT(fname_a, cat_a, jnum_a, seq_a);
	MAP_TO_CAT(fname_b, cat_b, jnum_b, seq_b);

#undef MAP_TO_CAT

	/* First handle all cases which have "other" files */
	if ((cat_a >= cat_other) || (cat_b >= cat_other)) {
		/* for two "other" files, just compare the full name */
		if (cat_a == cat_b)
			res = strcmp(fname_a, fname_b);
		else if (cat_a < cat_b)
			res = a_lt_b;
		else
			res = a_gt_b;
		goto have_res;
	}

	/*
	 * At this point, we know both files are legitimate `cf', `df', `rf',
	 * or `tf' files.  Compare them by job-number and machine name.
	 */
	res = strcmp(jnum_a, jnum_b);
	if (res != 0)
		goto have_res;

	/*
	 * We have two files which belong to the same job.  Sort based
	 * on the category of file (`c' before `d', etc).
	 */
	if (cat_a < cat_b) {
		res = a_lt_b;
		goto have_res;
	} else if (cat_a > cat_b) {
		res = a_gt_b;
		goto have_res;
	}

	/*
	 * Two files in the same category for a single job.  Sort based
	 * on the sequence letter(s).  (usually `A' through `Z', etc).
	 */
	if (seq_a < seq_b) {
		res = a_lt_b;
		goto have_res;
	} else if (seq_a > seq_b) {
		res = a_gt_b;
		goto have_res;
	}

	/*
	 * Given that the filenames in a directory are unique, this SHOULD
	 * never happen (unless there are logic errors in this routine).
	 * But if it does happen, we must return "is equal" or the caller
	 * might see inconsistent results in the sorting order, and that
	 * can trigger other problems.
	 */
	printf("\t*** Error in sortq: %s == %s !\n", fname_a, fname_b);
	printf("\t***       cat %d == %d ; seq = %d %d\n", cat_a, cat_b,
	    seq_a, seq_b);
	res = 0;

have_res:
	return res;
}