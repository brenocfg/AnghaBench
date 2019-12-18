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
struct TYPE_2__ {int tabsize; } ;

/* Variables and functions */
 TYPE_1__ opt ; 

int
count_spaces_until(int cur, char *buffer, char *end)
/*
 * this routine figures out where the character position will be after
 * printing the text in buffer starting at column "current"
 */
{
    char *buf;		/* used to look thru buffer */

    for (buf = buffer; *buf != '\0' && buf != end; ++buf) {
	switch (*buf) {

	case '\n':
	case 014:		/* form feed */
	    cur = 1;
	    break;

	case '\t':
	    cur = opt.tabsize * (1 + (cur - 1) / opt.tabsize) + 1;
	    break;

	case 010:		/* backspace */
	    --cur;
	    break;

	default:
	    ++cur;
	    break;
	}			/* end of switch */
    }				/* end of for loop */
    return (cur);
}