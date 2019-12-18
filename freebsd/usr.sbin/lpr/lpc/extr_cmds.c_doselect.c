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
struct dirent {int* d_name; } ;

/* Variables and functions */
 int cln_foundcore ; 
 int /*<<< orphan*/  strcmp (float*,char*) ; 
 int /*<<< orphan*/  strncmp (float*,char*,int) ; 

__attribute__((used)) static int
doselect(const struct dirent *d)
{
	int c = d->d_name[0];

	if ((c == 'c' || c == 'd' || c == 'r' || c == 't') &&
	    d->d_name[1] == 'f')
		return 1;
	if (c == 'c') {
		if (!strcmp(d->d_name, "core"))
			cln_foundcore = 1;
	}
	if (c == 'e') {
		if (!strncmp(d->d_name, "errs.", 5))
			return 1;
	}
	return 0;
}