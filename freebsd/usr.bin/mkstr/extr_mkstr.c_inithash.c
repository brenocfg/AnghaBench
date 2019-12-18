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
 scalar_t__ fgetNUL (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashit (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mesgread ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

void
inithash(void)
{
	char buf[512];
	int mesgpt = 0;

	rewind(mesgread);
	while (fgetNUL(buf, sizeof buf, mesgread) != 0) {
		hashit(buf, 0, mesgpt);
		mesgpt += strlen(buf) + 2;
	}
}