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
struct archiver {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct archiver const** archivers ; 
 int nr_archivers ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct archiver *lookup_archiver(const char *name)
{
	int i;

	if (!name)
		return NULL;

	for (i = 0; i < nr_archivers; i++) {
		if (!strcmp(name, archivers[i]->name))
			return archivers[i];
	}
	return NULL;
}