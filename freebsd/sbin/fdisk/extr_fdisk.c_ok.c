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
 int /*<<< orphan*/  LBUF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* lbuf ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,char*) ; 
 int strlen (scalar_t__*) ; 

__attribute__((used)) static int
ok(const char *str)
{
	printf("%s [n] ", str);
	fflush(stdout);
	if (fgets(lbuf, LBUF, stdin) == NULL)
		exit(1);
	lbuf[strlen(lbuf)-1] = 0;

	if (*lbuf &&
		(!strcmp(lbuf, "yes") || !strcmp(lbuf, "YES") ||
		 !strcmp(lbuf, "y") || !strcmp(lbuf, "Y")))
		return 1;
	else
		return 0;
}