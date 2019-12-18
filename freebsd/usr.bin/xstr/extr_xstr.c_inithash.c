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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgetNUL (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hashit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesgpt ; 
 int /*<<< orphan*/  strings ; 
 int /*<<< orphan*/  tellpt ; 

__attribute__((used)) static void
inithash(void)
{
	char buf[BUFSIZ];
	FILE *mesgread = fopen(strings, "r");

	if (mesgread == NULL)
		return;
	for (;;) {
		mesgpt = tellpt;
		if (fgetNUL(buf, sizeof buf, mesgread) == 0)
			break;
		ignore(hashit(buf, 0));
	}
	ignore(fclose(mesgread));
}