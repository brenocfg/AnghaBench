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
typedef  scalar_t__ uid_t ;
typedef  enum nss_lookup_type { ____Placeholder_nss_lookup_type } nss_lookup_type ;

/* Variables and functions */
 int NS_NOTFOUND ; 
 int NS_SUCCESS ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 int nss_lt_all ; 
 int nss_lt_name ; 
 size_t strlen (char const*) ; 
 unsigned long strtoul (char const*,char**,int) ; 

int
__pw_match_entry(const char *entry, size_t entrysize, enum nss_lookup_type how,
    const char *name, uid_t uid)
{
	const char	*p, *eom;
	char		*q;
	size_t		 len;
	unsigned long	 m;

	eom = entry + entrysize;
	for (p = entry; p < eom; p++)
		if (*p == ':')
			break;
	if (*p != ':')
		return (NS_NOTFOUND);
	if (how == nss_lt_all)
		return (NS_SUCCESS);
	if (how == nss_lt_name) {
		len = strlen(name);
		if (len == (p - entry) && memcmp(name, entry, len) == 0)
			return (NS_SUCCESS);
		else
			return (NS_NOTFOUND);
	}
	for (p++; p < eom; p++)
		if (*p == ':')
			break;
	if (*p != ':')
		return (NS_NOTFOUND);
	m = strtoul(++p, &q, 10);
	if (q[0] != ':' || (uid_t)m != uid)
		return (NS_NOTFOUND);
	else
		return (NS_SUCCESS);
}