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
struct kod_entry {int /*<<< orphan*/  hostname; } ;

/* Variables and functions */
 struct kod_entry* eallocarray (int,int) ; 
 struct kod_entry** kod_db ; 
 int kod_db_cnt ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int
search_entry(
	const char *hostname,
	struct kod_entry **dst
	)
{
	register int a, b, resc = 0;

	for (a = 0; a < kod_db_cnt; a++)
		if (!strcmp(kod_db[a]->hostname, hostname))
			resc++;

	if (!resc) {
		*dst = NULL;
		return 0;
	}

	*dst = eallocarray(resc, sizeof(**dst));

	b = 0;
	for (a = 0; a < kod_db_cnt; a++)
		if (!strcmp(kod_db[a]->hostname, hostname)) {
			(*dst)[b] = *kod_db[a];
			b++;
		}

	return resc;
}