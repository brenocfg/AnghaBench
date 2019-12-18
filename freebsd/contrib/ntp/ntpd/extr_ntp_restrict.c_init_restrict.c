#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ippeerlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_SLIST (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 TYPE_1__ restrict_def4 ; 
 TYPE_1__ restrict_def6 ; 
 int restrictcount ; 
 int /*<<< orphan*/  restrictlist4 ; 
 int /*<<< orphan*/  restrictlist6 ; 

void
init_restrict(void)
{
	/*
	 * The restriction lists begin with a default entry with address
	 * and mask 0, which will match any entry.  The lists are kept
	 * sorted by descending address followed by descending mask:
	 *
	 *   address	  mask
	 * 192.168.0.0	255.255.255.0	kod limited noquery nopeer
	 * 192.168.0.0	255.255.0.0	kod limited
	 * 0.0.0.0	0.0.0.0		kod limited noquery
	 *
	 * The first entry which matches an address is used.  With the
	 * example restrictions above, 192.168.0.0/24 matches the first
	 * entry, the rest of 192.168.0.0/16 matches the second, and
	 * everything else matches the third (default).
	 *
	 * Note this achieves the same result a little more efficiently
	 * than the documented behavior, which is to keep the lists
	 * sorted by ascending address followed by ascending mask, with
	 * the _last_ matching entry used.
	 *
	 * An additional wrinkle is we may have multiple entries with
	 * the same address and mask but differing match flags (mflags).
	 * At present there is only one, RESM_NTPONLY.  Entries with
	 * RESM_NTPONLY are sorted earlier so they take precedence over
	 * any otherwise similar entry without.  Again, this is the same
	 * behavior as but reversed implementation compared to the docs.
	 * 
	 */

	restrict_def4.ippeerlimit = -1;		/* Cleaner if we have C99 */
	restrict_def6.ippeerlimit = -1;		/* Cleaner if we have C99 */

	LINK_SLIST(restrictlist4, &restrict_def4, link);
	LINK_SLIST(restrictlist6, &restrict_def6, link);
	restrictcount = 2;
}