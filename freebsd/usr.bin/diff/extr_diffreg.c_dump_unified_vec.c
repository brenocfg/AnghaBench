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
 int /*<<< orphan*/  uni_range (int,int) ; 

__attribute__((used)) static void
dump_unified_vec(FILE *f1, FILE *f2, int flags)
{
	struct context_vec *cvp = context_vec_start;
	int lowa, upb, lowc, upd;
	int a, b, c, d;
	char ch, *f;

	if (context_vec_start > context_vec_ptr)
		return;

	b = d = 0;		/* gcc */
	lowa = MAX(1, cvp->a - diff_context);
	upb = MIN(len[0], context_vec_ptr->b + diff_context);
	lowc = MAX(1, cvp->c - diff_context);
	upd = MIN(len[1], context_vec_ptr->d + diff_context);

	diff_output("@@ -");
	uni_range(lowa, upb);
	diff_output(" +");
	uni_range(lowc, upd);
	diff_output(" @@");
	if ((flags & D_PROTOTYPE)) {
		f = match_function(ixold, lowa-1, f1);
		if (f != NULL)
			diff_output(" %s", f);
	}
	diff_output("\n");

	/*
	 * Output changes in "unified" diff format--the old and new lines
	 * are printed together.
	 */
	for (; cvp <= context_vec_ptr; cvp++) {
		a = cvp->a;
		b = cvp->b;
		c = cvp->c;
		d = cvp->d;

		/*
		 * c: both new and old changes
		 * d: only changes in the old file
		 * a: only changes in the new file
		 */
		if (a <= b && c <= d)
			ch = 'c';
		else
			ch = (a <= b) ? 'd' : 'a';

		switch (ch) {
		case 'c':
			fetch(ixold, lowa, a - 1, f1, ' ', 0, flags);
			fetch(ixold, a, b, f1, '-', 0, flags);
			fetch(ixnew, c, d, f2, '+', 0, flags);
			break;
		case 'd':
			fetch(ixold, lowa, a - 1, f1, ' ', 0, flags);
			fetch(ixold, a, b, f1, '-', 0, flags);
			break;
		case 'a':
			fetch(ixnew, lowc, c - 1, f2, ' ', 0, flags);
			fetch(ixnew, c, d, f2, '+', 0, flags);
			break;
		}
		lowa = b + 1;
		lowc = d + 1;
	}
	fetch(ixnew, d + 1, upd, f2, ' ', 0, flags);

	context_vec_ptr = context_vec_start - 1;
}