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
typedef  char kod_entry ;
struct addrinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (int,char*) ; 
 char* addrinfo_to_str (struct addrinfo const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ search_entry (char*,char**) ; 

int
check_kod(
	const struct addrinfo *	ai
	)
{
	char *hostname;
	struct kod_entry *reason;

	/* Is there a KoD on file for this address? */
	hostname = addrinfo_to_str(ai);
	TRACE(2, ("check_kod: checking <%s>\n", hostname));
	if (search_entry(hostname, &reason)) {
		printf("prior KoD for %s, skipping.\n",
			hostname);
		free(reason);
		free(hostname);

		return 1;
	}
	free(hostname);

	return 0;
}