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
 char const HASH_DELIM ; 
 char* host_hash (char const*,char const*,size_t) ; 
 int match_hostname (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
match_maybe_hashed(const char *host, const char *names, int *was_hashed)
{
	int hashed = *names == HASH_DELIM;
	const char *hashed_host;
	size_t nlen = strlen(names);

	if (was_hashed != NULL)
		*was_hashed = hashed;
	if (hashed) {
		if ((hashed_host = host_hash(host, names, nlen)) == NULL)
			return -1;
		return nlen == strlen(hashed_host) &&
		    strncmp(hashed_host, names, nlen) == 0;
	}
	return match_hostname(host, names) == 1;
}