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
struct entry {int /*<<< orphan*/  e_name; struct entry* e_sibling; struct entry* e_entries; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  UFS_ROOTINO ; 
 struct entry* lookupino (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

struct entry *
lookupname(char *name)
{
	struct entry *ep;
	char *np, *cp;
	char buf[MAXPATHLEN];

	cp = name;
	for (ep = lookupino(UFS_ROOTINO); ep != NULL; ep = ep->e_entries) {
		for (np = buf; *cp != '/' && *cp != '\0' &&
				np < &buf[sizeof(buf)]; )
			*np++ = *cp++;
		if (np == &buf[sizeof(buf)])
			break;
		*np = '\0';
		for ( ; ep != NULL; ep = ep->e_sibling)
			if (strcmp(ep->e_name, buf) == 0)
				break;
		if (ep == NULL)
			break;
		if (*cp++ == '\0')
			return (ep);
	}
	return (NULL);
}