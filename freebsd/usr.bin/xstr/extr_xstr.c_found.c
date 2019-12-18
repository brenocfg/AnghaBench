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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  prstr (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ vflg ; 

__attribute__((used)) static void
found(int new, off_t off, char *str)
{
	if (vflg == 0)
		return;
	if (!new)
		fprintf(stderr, "found at %d:", (int) off);
	else
		fprintf(stderr, "new at %d:", (int) off);
	prstr(str);
	fprintf(stderr, "\n");
}