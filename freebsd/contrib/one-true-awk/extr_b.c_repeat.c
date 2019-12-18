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
typedef  int /*<<< orphan*/  uschar ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  REPEAT_PLUS_APPENDED ; 
 int /*<<< orphan*/  REPEAT_SIMPLE ; 
 int /*<<< orphan*/  REPEAT_WITH_Q ; 
 int /*<<< orphan*/  REPEAT_ZERO ; 
 int replace_repeat (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int repeat(const uschar *reptok, int reptoklen, const uschar *atom,
		  int atomlen, int firstnum, int secondnum)
{
	/*
	   In general, the repetition specifier or "bound" is replaced here
	   by an equivalent ERE string, repeating the immediately previous atom
	   and appending ? and + as needed. Note that the first copy of the
	   atom is left in place, except in the special_case of a zero-repeat
	   (i.e., {0}).
	 */
	if (secondnum < 0) {	/* means {n,} -> repeat n-1 times followed by PLUS */
		if (firstnum < 2) {
			/* 0 or 1: should be handled before you get here */
			FATAL("internal error");
		} else {
			return replace_repeat(reptok, reptoklen, atom, atomlen,
				firstnum, secondnum, REPEAT_PLUS_APPENDED);
		}
	} else if (firstnum == secondnum) {	/* {n} or {n,n} -> simply repeat n-1 times */
		if (firstnum == 0) {	/* {0} or {0,0} */
			/* This case is unusual because the resulting
			   replacement string might actually be SMALLER than
			   the original ERE */
			return replace_repeat(reptok, reptoklen, atom, atomlen,
					firstnum, secondnum, REPEAT_ZERO);
		} else {		/* (firstnum >= 1) */
			return replace_repeat(reptok, reptoklen, atom, atomlen,
					firstnum, secondnum, REPEAT_SIMPLE);
		}
	} else if (firstnum < secondnum) {	/* {n,m} -> repeat n-1 times then alternate  */
		/*  x{n,m}  =>  xx...x{1, m-n+1}  =>  xx...x?x?x?..x?	*/
		return replace_repeat(reptok, reptoklen, atom, atomlen,
					firstnum, secondnum, REPEAT_WITH_Q);
	} else {	/* Error - shouldn't be here (n>m) */
		FATAL("internal error");
	}
	return 0;
}