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
 int BUFSIZ ; 
 scalar_t__ err ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/ * fgets (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  fputs (char*,scalar_t__) ; 
 int /*<<< orphan*/  rewind (scalar_t__) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 

void
flsh_errs(void)
{
	char buf[BUFSIZ];

	(void)fflush(stdout);
	(void)fflush(err);
	if (err == stderr)
		return;
	rewind(err);
	while (fgets(buf, BUFSIZ, err) != NULL)
		(void)fputs(buf, stderr);
}