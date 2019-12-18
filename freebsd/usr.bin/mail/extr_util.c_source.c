#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ s_loading; int /*<<< orphan*/  s_cond; int /*<<< orphan*/ * s_file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CANY ; 
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Fopen (char*,char*) ; 
 int SSTACK_SIZE ; 
 int /*<<< orphan*/  cond ; 
 char* expand (char*) ; 
 int /*<<< orphan*/ * input ; 
 scalar_t__ loading ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sourcing ; 
 int ssp ; 
 TYPE_1__* sstack ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
source(char **arglist)
{
	FILE *fi;
	char *cp;

	if ((cp = expand(*arglist)) == NULL)
		return (1);
	if ((fi = Fopen(cp, "r")) == NULL) {
		warn("%s", cp);
		return (1);
	}
	if (ssp >= SSTACK_SIZE - 1) {
		printf("Too much \"sourcing\" going on.\n");
		(void)Fclose(fi);
		return (1);
	}
	sstack[ssp].s_file = input;
	sstack[ssp].s_cond = cond;
	sstack[ssp].s_loading = loading;
	ssp++;
	loading = 0;
	cond = CANY;
	input = fi;
	sourcing++;
	return (0);
}