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
 int atoi (char const*) ; 
 int expr (char const*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pushback (char const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
dosub(const char *argv[], int argc)
{
	const char *ap, *fc, *k;
	int nc;

	ap = argv[2];		       /* target string */
#ifdef EXPR
	fc = ap + expr(argv[3]);       /* first char */
#else
	fc = ap + atoi(argv[3]);       /* first char */
#endif
	nc = strlen(fc);
	if (argc >= 5)
#ifdef EXPR
		nc = min(nc, expr(argv[4]));
#else
		nc = min(nc, atoi(argv[4]));
#endif
	if (fc >= ap && fc < ap + strlen(ap))
		for (k = fc + nc - 1; k >= fc; k--)
			pushback(*k);
}