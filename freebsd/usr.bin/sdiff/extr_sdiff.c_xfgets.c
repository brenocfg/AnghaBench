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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
xfgets(FILE *file)
{
	size_t linecap;
	ssize_t l;
	char *s;

	clearerr(file);
	linecap = 0;
	s = NULL;

	if ((l = getline(&s, &linecap, file)) == -1) {
		if (ferror(file))
			err(2, "error reading file");
		return (NULL);
	}

	if (s[l-1] == '\n')
		s[l-1] = '\0';

	return (s);
}