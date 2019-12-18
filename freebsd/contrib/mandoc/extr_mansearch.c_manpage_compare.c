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
struct manpage {int bits; int sec; scalar_t__ names; } ;

/* Variables and functions */
 int strcasecmp (char const*,char const*) ; 
 char* strchr (scalar_t__,char) ; 
 size_t strcspn (scalar_t__,char*) ; 
 int strncasecmp (scalar_t__,scalar_t__,size_t) ; 

__attribute__((used)) static int
manpage_compare(const void *vp1, const void *vp2)
{
	const struct manpage	*mp1, *mp2;
	const char		*cp1, *cp2;
	size_t			 sz1, sz2;
	int			 diff;

	mp1 = vp1;
	mp2 = vp2;
	if ((diff = mp2->bits - mp1->bits) ||
	    (diff = mp1->sec - mp2->sec))
		return diff;

	/* Fall back to alphabetic ordering of names. */
	sz1 = strcspn(mp1->names, "(");
	sz2 = strcspn(mp2->names, "(");
	if (sz1 < sz2)
		sz1 = sz2;
	if ((diff = strncasecmp(mp1->names, mp2->names, sz1)))
		return diff;

	/* For identical names and sections, prefer arch-dependent. */
	cp1 = strchr(mp1->names + sz1, '/');
	cp2 = strchr(mp2->names + sz2, '/');
	return cp1 != NULL && cp2 != NULL ? strcasecmp(cp1, cp2) :
	    cp1 != NULL ? -1 : cp2 != NULL ? 1 : 0;
}