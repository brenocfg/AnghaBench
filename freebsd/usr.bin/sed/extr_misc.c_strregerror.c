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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 size_t regerror (int,int /*<<< orphan*/ *,char*,size_t) ; 

char *
strregerror(int errcode, regex_t *preg)
{
	static char *oe;
	size_t s;

	if (oe != NULL)
		free(oe);
	s = regerror(errcode, preg, NULL, 0);
	if ((oe = malloc(s)) == NULL)
		err(1, "malloc");
	(void)regerror(errcode, preg, oe, s);
	return (oe);
}