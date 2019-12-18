#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tabsize; scalar_t__ use_tabs; } ;

/* Variables and functions */
 TYPE_1__ opt ; 
 int /*<<< orphan*/  output ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pad_output(int current, int target)
			        /* writes tabs and blanks (if necessary) to
				 * get the current output position up to the
				 * target column */
    /* current: the current column value */
    /* target: position we want it at */
{
    int curr;			/* internal column pointer */

    if (current >= target)
	return (current);	/* line is already long enough */
    curr = current;
    if (opt.use_tabs) {
	int tcur;

	while ((tcur = opt.tabsize * (1 + (curr - 1) / opt.tabsize) + 1) <= target) {
	    putc('\t', output);
	    curr = tcur;
	}
    }
    while (curr++ < target)
	putc(' ', output);	/* pad with final blanks */

    return (target);
}