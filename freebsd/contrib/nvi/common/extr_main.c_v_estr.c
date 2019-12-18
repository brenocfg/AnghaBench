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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
v_estr(
	char *name,
	int eno,
	char *msg)
{
	(void)fprintf(stderr, "%s", name);
	if (msg != NULL)
		(void)fprintf(stderr, ": %s", msg);
	if (eno)
		(void)fprintf(stderr, ": %s", strerror(errno));
	(void)fprintf(stderr, "\n");
}