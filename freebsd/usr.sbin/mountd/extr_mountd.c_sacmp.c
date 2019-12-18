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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET6 128 
 int memcmp (unsigned char*,unsigned char*,int) ; 
 unsigned char* sa_rawaddr (struct sockaddr*,int*) ; 

__attribute__((used)) static int
sacmp(struct sockaddr *sa1, struct sockaddr *sa2, struct sockaddr *samask)
{
	unsigned char *p1, *p2, *mask;
	int len, i;

	if (sa1->sa_family != sa2->sa_family ||
	    (p1 = sa_rawaddr(sa1, &len)) == NULL ||
	    (p2 = sa_rawaddr(sa2, NULL)) == NULL)
		return (1);

	switch (sa1->sa_family) {
	case AF_INET6:
		if (((struct sockaddr_in6 *)sa1)->sin6_scope_id !=
		    ((struct sockaddr_in6 *)sa2)->sin6_scope_id)
			return (1);
		break;
	}

	/* Simple binary comparison if no mask specified. */
	if (samask == NULL)
		return (memcmp(p1, p2, len));

	/* Set up the mask, and do a mask-based comparison. */
	if (sa1->sa_family != samask->sa_family ||
	    (mask = sa_rawaddr(samask, NULL)) == NULL)
		return (1);

	for (i = 0; i < len; i++)
		if ((p1[i] & mask[i]) != (p2[i] & mask[i]))
			return (1);
	return (0);
}