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
 int /*<<< orphan*/  autoboot (int,int /*<<< orphan*/ *) ; 
 scalar_t__ autoboot_tried ; 
 char* getenv (char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

void
autoboot_maybe()
{
	char	*cp;

	cp = getenv("autoboot_delay");
	if ((autoboot_tried == 0) && ((cp == NULL) || strcasecmp(cp, "NO")))
		autoboot(-1, NULL);		/* try to boot automatically */
}