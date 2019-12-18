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

int
cgetmatch(const char *buf, const char *name)
{
    const char *np, *bp;

    /*
     * Start search at beginning of record.
     */
    bp = buf;
    for (;;) {
	/*
	 * Try to match a record name.
	 */
	np = name;
	for (;;)
	    if (*np == '\0') {
		if (*bp == '|' || *bp == ':' || *bp == '\0')
		    return (0);
		else
		    break;
	    } else
		if (*bp++ != *np++)
		    break;

	/*
	 * Match failed, skip to next name in record.
	 */
	bp--;	/* a '|' or ':' may have stopped the match */
	for (;;)
	    if (*bp == '\0' || *bp == ':')
		return (-1);	/* match failed totally */
	    else
		if (*bp++ == '|')
		    break;	/* found next name */
    }
}