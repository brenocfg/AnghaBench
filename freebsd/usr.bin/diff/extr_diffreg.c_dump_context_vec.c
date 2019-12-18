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
struct context_vec {int a; int b; int c; int d; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int D_PROTOTYPE ; 
 int MAX (int,scalar_t__) ; 
 int MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 struct context_vec* context_vec_ptr ; 
 struct context_vec* context_vec_start ; 
 scalar_t__ diff_context ; 
 int /*<<< orphan*/  diff_output (char*,...) ; 
 int /*<<< orphan*/  fetch (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,char,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ixnew ; 
 int /*<<< orphan*/  ixold ; 
 int /*<<< orphan*/ * len ; 
 char* match_function (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range (int,int,char*) ; 

__attribute__((used)) static void
dump_context_vec(FILE *f1, FILE *f2, int flags)
{
	struct context_vec *cvp = context_vec_start;
	int lowa, upb, lowc, upd, do_output;
	int a, b, c, d;
	char ch, *f;

	if (context_vec_start > context_vec_ptr)
		return;

	b = d = 0;		/* gcc */
	lowa = MAX(1, cvp->a - diff_context);
	upb = MIN(len[0], context_vec_ptr->b + diff_context);
	lowc = MAX(1, cvp->c - diff_context);
	upd = MIN(len[1], context_vec_ptr->d + diff_context);

	diff_output("***************");
	if ((flags & D_PROTOTYPE)) {
		f = match_function(ixold, lowa-1, f1);
		if (f != NULL)
			diff_output(" %s", f);
	}
	diff_output("\n*** ");
	range(lowa, upb, ",");
	diff_output(" ****\n");

	/*
	 * Output changes to the "old" file.  The first loop suppresses
	 * output if there were no changes to the "old" file (we'll see
	 * the "old" lines as context in the "new" list).
	 */
	do_output = 0;
	for (; cvp <= context_vec_ptr; cvp++)
		if (cvp->a <= cvp->b) {
			cvp = context_vec_start;
			do_output++;
			break;
		}
	if (do_output) {
		while (cvp <= context_vec_ptr) {
			a = cvp->a;
			b = cvp->b;
			c = cvp->c;
			d = cvp->d;

			if (a <= b && c <= d)
				ch = 'c';
			else
				ch = (a <= b) ? 'd' : 'a';

			if (ch == 'a')
				fetch(ixold, lowa, b, f1, ' ', 0, flags);
			else {
				fetch(ixold, lowa, a - 1, f1, ' ', 0, flags);
				fetch(ixold, a, b, f1,
				    ch == 'c' ? '!' : '-', 0, flags);
			}
			lowa = b + 1;
			cvp++;
		}
		fetch(ixold, b + 1, upb, f1, ' ', 0, flags);
	}
	/* output changes to the "new" file */
	diff_output("--- ");
	range(lowc, upd, ",");
	diff_output(" ----\n");

	do_output = 0;
	for (cvp = context_vec_start; cvp <= context_vec_ptr; cvp++)
		if (cvp->c <= cvp->d) {
			cvp = context_vec_start;
			do_output++;
			break;
		}
	if (do_output) {
		while (cvp <= context_vec_ptr) {
			a = cvp->a;
			b = cvp->b;
			c = cvp->c;
			d = cvp->d;

			if (a <= b && c <= d)
				ch = 'c';
			else
				ch = (a <= b) ? 'd' : 'a';

			if (ch == 'd')
				fetch(ixnew, lowc, d, f2, ' ', 0, flags);
			else {
				fetch(ixnew, lowc, c - 1, f2, ' ', 0, flags);
				fetch(ixnew, c, d, f2,
				    ch == 'c' ? '!' : '+', 0, flags);
			}
			lowc = d + 1;
			cvp++;
		}
		fetch(ixnew, d + 1, upd, f2, ' ', 0, flags);
	}
	context_vec_ptr = context_vec_start - 1;
}