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
struct libalias {int dummy; } ;
struct alias_data {scalar_t__ maxpktsize; int /*<<< orphan*/ * sport; int /*<<< orphan*/ * dport; int /*<<< orphan*/ * lnk; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fingerprint(struct libalias *la, struct alias_data *ah)
{

	/*
	 * Check here all the data that will be used later, if any field
	 * is empy/NULL, return a -1 value.
	 */
	if (ah->dport == NULL || ah->sport == NULL || ah->lnk == NULL ||
		ah->maxpktsize == 0)
		return (-1);
	/*
	 * Fingerprint the incoming packet, if it matches any conditions
	 * return an OK value.
	 */
	if (ntohs(*ah->dport) == 123
	    || ntohs(*ah->sport) == 456)
		return (0); /* I know how to handle it. */
	return (-1); /* I don't recognize this packet. */
}