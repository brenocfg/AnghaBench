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
typedef  int /*<<< orphan*/  gid_t ;
typedef  enum nss_lookup_type { ____Placeholder_nss_lookup_type } nss_lookup_type ;

/* Variables and functions */
 int NS_NOTFOUND ; 
 int NS_SUCCESS ; 
 scalar_t__ is_comment_line (char const*,size_t) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
#define  nss_lt_all 130 
#define  nss_lt_id 129 
#define  nss_lt_name 128 
 size_t strlen (char const*) ; 
 unsigned long strtoul (char const*,char**,int) ; 

int
__gr_match_entry(const char *line, size_t linesize, enum nss_lookup_type how,
    const char *name, gid_t gid)
{
	size_t		 namesize;
	const char	*p, *eol;
	char		*q;
	unsigned long	 n;
	int		 i, needed;

	if (linesize == 0 || is_comment_line(line, linesize))
		return (NS_NOTFOUND);
	switch (how) {
	case nss_lt_name:	needed = 1; break;
	case nss_lt_id:		needed = 2; break;
	default:		needed = 2; break;
	}
	eol = &line[linesize];
	for (p = line, i = 0; i < needed && p < eol; p++)
		if (*p == ':')
			i++;
	if (i < needed)
		return (NS_NOTFOUND);
	switch (how) {
	case nss_lt_name:
		namesize = strlen(name);
		if (namesize + 1 == (size_t)(p - line) &&
		    memcmp(line, name, namesize) == 0)
			return (NS_SUCCESS);
		break;
	case nss_lt_id:
		n = strtoul(p, &q, 10);
		if (q < eol && *q == ':' && gid == (gid_t)n)
			return (NS_SUCCESS);
		break;
	case nss_lt_all:
		return (NS_SUCCESS);
	default:
		break;
	}
	return (NS_NOTFOUND);
}