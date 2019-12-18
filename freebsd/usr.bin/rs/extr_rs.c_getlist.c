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
 short atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,short) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static char *
getlist(short **list, char *p)
{
	int count = 1;
	char *t;

	for (t = p + 1; *t; t++) {
		if (!isdigit((unsigned char)*t))
			errx(1,
	"option %.1s requires a list of unsigned numbers separated by commas", t);
		count++;
		while (*t && isdigit((unsigned char)*t))
			t++;
		if (*t != ',')
			break;
	}
	if (!(*list = (short *) malloc(count * sizeof(short))))
		errx(1, "no list space");
	count = 0;
	for (t = p + 1; *t; t++) {
		(*list)[count++] = atoi(t);
		printf("++ %d ", (*list)[count-1]);
		fflush(stdout);
		while (*t && isdigit((unsigned char)*t))
			t++;
		if (*t != ',')
			break;
	}
	(*list)[count] = 0;
	return(t - 1);
}