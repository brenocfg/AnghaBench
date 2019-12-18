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
 int /*<<< orphan*/  bf_init () ; 
 int /*<<< orphan*/  interp_include (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 

void
interp_init(void)
{

	setenv("script.lang", "forth", 1);
	bf_init();
	/* Read our default configuration. */
	interp_include("/boot/loader.rc");
}